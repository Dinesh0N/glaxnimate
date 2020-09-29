#pragma once

#include "model/animation/animatable.hpp"
#include "model/object.hpp"

#include <QTransform>


namespace model {


class Transform : public ObjectBase<Transform, Object>
{
    GLAXNIMATE_OBJECT
    GLAXNIMATE_ANIMATABLE(QPointF, anchor_point, QPointF(0, 0))
    GLAXNIMATE_ANIMATABLE(QPointF, position, QPointF(0, 0))
    GLAXNIMATE_ANIMATABLE(QVector2D, scale, QVector2D(1, 1))
    GLAXNIMATE_ANIMATABLE(float, rotation, 0, {}, 0, 360, true)

public:
    using Ctor::Ctor;

    virtual QString type_name_human() const override { return tr("Transform"); }

    QTransform transform_matrix(FrameTime f) const;
    void set_transform_matrix(const QTransform& t);
};



} // namespace model
