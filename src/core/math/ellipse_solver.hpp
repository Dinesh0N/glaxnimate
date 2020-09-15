#pragma once

#include <QPointF>
#include <QtMath>

#include "bezier.hpp"
#include "vector.hpp"

namespace math {

class EllipseSolver
{
public:
    /**
     * \param center      2D vector, center of the ellipse
     * \param radii       2D vector, x/y radius of the ellipse
     * \param xrot        Angle between the main axis of the ellipse and the x axis (in radians)
     */
    EllipseSolver(const QPointF& center, const QPointF& radii, qreal xrot)
        : center(center),
          radii(radii),
          xrot(xrot)
    {}

    QPointF point(qreal t) const
    {
        return QPointF(
            center.x()
            + radii.x() * qCos(xrot) * qCos(t)
            - radii.y() * qSin(xrot) * qSin(t),

            center.y()
            + radii.x() * qSin(xrot) * qCos(t)
            + radii.y() * qCos(xrot) * qSin(t)
        );
    }

    QPointF derivative(qreal t) const
    {
        return QPointF(
            - radii.x() * qCos(xrot) * qSin(t)
            - radii.y() * qSin(xrot) * qCos(t),

            - radii.x() * qSin(xrot) * qSin(t)
            + radii.y() * qCos(xrot) * qCos(t)
        );
    }

    Bezier to_bezier(qreal anglestart, qreal angle_delta)
    {
        Bezier points;
        qreal angle1 = anglestart;
        qreal angle_left = qAbs(angle_delta);
        qreal step = M_PI / 2;
        qreal sign = anglestart+angle_delta < angle1 ? -1 : 1;

        // We need to fix the first handle
        qreal firststep = qMin(angle_left, step) * sign;
        qreal alpha = _alpha(firststep);
        QPointF q1 = derivative(angle1) * alpha;
        points.push_back(BezierPoint::from_relative(point(angle1), QPointF(0, 0), q1, math::Symmetrical));

        // Then we iterate until the angle has been completed
        qreal tolerance = step / 2;
        while ( angle_left > tolerance )
        {
            qreal lstep = qMin(angle_left, step);
            qreal step_sign = lstep * sign;
            qreal angle2 = angle1 + step_sign;
            angle_left -= abs(lstep);

            alpha = _alpha(step_sign);
            QPointF p2 = point(angle2);
            QPointF q2 = derivative(angle2) * alpha;

            points.push_back(BezierPoint::from_relative(p2, -q2, q2, math::Symmetrical));
            angle1 = angle2;
        }
        return points;
    }

    static Bezier from_svg_arc(
        QPointF start, qreal rx, qreal ry, qreal xrot,
        bool large, bool sweep, QPointF dest
    )
    {
        rx = qAbs(rx);
        ry = qAbs(ry);

        qreal x1 = start.x();
        qreal y1 = start.y();
        qreal x2 = dest.x();
        qreal y2 = dest.y();
        qreal phi = M_PI * xrot / 180;

        QPointF p1 = _matrix_mul(phi, (start-dest)/2, -1);
        qreal x1p = p1.x();
        qreal y1p = p1.y();

        qreal cr = (x1p * x1p) / (rx * rx) + (y1p * y1p) / (ry * ry);
        if ( cr > 1 )
        {
            qreal s = qSqrt(cr);
            rx *= s;
            ry *= s;
        }

        qreal dq = rx * rx * y1p * y1p + ry * ry * x1p * x1p;
        qreal pq = (rx * rx * ry * ry - dq) / dq;
        qreal cpm = qSqrt(qMax(0., pq));
        if ( large == sweep )
            cpm = -cpm;
        QPointF cp(cpm * rx * y1p / ry, -cpm * ry * x1p / rx);
        QPointF c = _matrix_mul(phi, cp) + QPointF((x1+x2)/2, (y1+y2)/2);
        qreal theta1 = _angle(QPointF(1, 0), QPointF((x1p - cp.x()) / rx, (y1p - cp.y()) / ry));
        qreal deltatheta = std::fmod(_angle(
            QPointF((x1p - cp.x()) / rx, (y1p - cp.y()) / ry),
            QPointF((-x1p - cp.x()) / rx, (-y1p - cp.y()) / ry)
        ), 2*M_PI);

        if ( !sweep && deltatheta > 0 )
            deltatheta -= 2*M_PI;
        else if ( sweep && deltatheta < 0 )
            deltatheta += 2*M_PI;

        return EllipseSolver(c, QPointF(rx, ry), phi).to_bezier(theta1, deltatheta);
    }

private:
    static qreal _alpha(qreal step)
    {
        return qSin(step) * (qSqrt(4+3*qPow(qTan(step/2), 2)) - 1) / 3;
    }


    static QPointF _matrix_mul(qreal phi, const QPointF p, qreal sin_mul=1)
    {
        qreal c = qCos(phi);
        qreal  s = qSin(phi) * sin_mul;

        qreal xr = c * p.x() - s * p.y();
        qreal yr = s * p.x() + c * p.y();
        return QPointF(xr, yr);

    }
    static qreal _angle(const QPointF& u, const QPointF& v)
    {
        qreal arg = qAcos(qMax(-1., qMin(1., QPointF::dotProduct(u, v) / (length(u) * length(v)))));
        if ( u.x() * v.y() - u.y() * v.x() < 0 )
            return -arg;
        return arg;
    }

    QPointF center;
    QPointF radii;
    qreal xrot;
};

} // namespace math

