#pragma once

#include <QGraphicsObject>

namespace model {

class DocumentNode;

} // namespace model

namespace model::graphics {

class DocumentNodeGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit DocumentNodeGraphicsItem(DocumentNode* node, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
//     QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    DocumentNode* node() const
    {
        return node_;
    }

public slots:
    void set_visible(bool v)
    {
        setVisible(v);
    }
    
    void shape_changed()
    {
        prepareGeometryChange();
    }
    
    
    void set_transform_matrix(const QTransform& t)
    {
        setTransform(t);
    }
/*
signals:
    void focused(DocumentNode* document_node);

protected:
    void focusInEvent(QFocusEvent *) override
    {
        emit focused(node);
    }*/

private:
    DocumentNode* node_;
};

} // namespace model::graphics
