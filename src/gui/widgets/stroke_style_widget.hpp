#ifndef STROKESTYLEWIDGET_H
#define STROKESTYLEWIDGET_H

#include <memory>
#include <QWidget>

#include "model/shapes/stroke.hpp"


class StrokeStyleWidget : public QWidget
{
    Q_OBJECT

public:
    StrokeStyleWidget(QWidget* parent = nullptr);

    ~StrokeStyleWidget();

    void save_settings() const;

    void set_cap_style(model::Stroke::Cap cap);
    void set_join_style(model::Stroke::Join join);

    QPen pen_style(const QBrush& color) const;

protected:
    void changeEvent ( QEvent* e ) override;
    void paintEvent(QPaintEvent * event) override;

private slots:
    void check_cap();
    void check_join();

private:
    class Private;
    std::unique_ptr<Private> d;
};

#endif // STROKESTYLEWIDGET_H
