#ifndef FRAMECONTROLSWIDGET_H
#define FRAMECONTROLSWIDGET_H

#include <QWidget>
#include <memory>

namespace Ui {
class FrameControlsWidget;
}
class FrameControlsWidget : public QWidget
{
    Q_OBJECT

public:
    FrameControlsWidget(QWidget* parent = nullptr);
    ~FrameControlsWidget();

    void set_range(int min, int max);
    void set_min(int min);
    void set_max(int max);
    void set_fps(qreal fps);

public slots:
    void play();
    void pause();

signals:
    void frame_selected(int frame);

private slots:
    void play_toggled(bool play);
    void commit_time();
    void go_first();
    void go_prev();
    void go_next();
    void go_last();


protected:
    void timerEvent(QTimerEvent* e) override;

protected:
    void changeEvent ( QEvent* e ) override;

private:
    qreal fps = 60;
    int timer = 0;
    std::unique_ptr<Ui::FrameControlsWidget> d;
};

#endif // FRAMECONTROLSWIDGET_H
