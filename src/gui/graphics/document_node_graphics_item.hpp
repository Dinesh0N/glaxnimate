#pragma once

#include <QGraphicsObject>

namespace model {

class DocumentNode;
class BaseProperty;

} // namespace model

namespace graphics {

class DocumentNodeGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    enum SelectionMode
    {
        None,
        Group,
        Shape,
    };

    explicit DocumentNodeGraphicsItem(model::DocumentNode* node, QGraphicsItem* parent = nullptr);
    ~DocumentNodeGraphicsItem();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    model::DocumentNode* node() const
    {
        return node_;
    }

    SelectionMode selection_mode() const { return selection_mode_; }
    void set_selection_mode(SelectionMode selection_mode) { selection_mode_ = selection_mode; }

public slots:
    void set_visible(bool v)
    {
        visible = v;
        setVisible(visible && visible_permitted);
    }

    void set_visible_permitted(bool v)
    {
        visible_permitted = v;
        setVisible(visible && visible_permitted);
    }

    void shape_changed();

    void set_transform_matrix(const QTransform& t)
    {
        setTransform(t);
    }

    void set_opacity(qreal op)
    {
        setOpacity(op);
    }

private slots:
    void on_property_changed(const model::BaseProperty* prop);

private:
    model::DocumentNode* node_;
    bool visible_permitted = true;
    bool visible = true;
    SelectionMode selection_mode_ = SelectionMode::Shape;
};

} // namespace graphics
