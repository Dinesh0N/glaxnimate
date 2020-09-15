#include "base.hpp"

namespace tools {

class FreehandTool : public Tool
{
public:
    QIcon icon() const override { return QIcon::fromTheme("draw-freehand"); }
    QString name() const override { return QObject::tr("Draw Freehand"); }
    QKeySequence key_sequence() const override { return QKeySequence(QObject::tr("F6"), QKeySequence::PortableText); }
    app::settings::SettingList settings() const override { return {}; }

    void mouse_press(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_move(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_release(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_double_click(const MouseEvent& event) override { Q_UNUSED(event); }
    void paint(const PaintEvent& event) override { Q_UNUSED(event); }
    void key_press(const KeyEvent& event) override { Q_UNUSED(event); }
    void key_release(const KeyEvent& event) override { Q_UNUSED(event); }
    QCursor cursor() override { return {}; }
    bool show_editors(model::DocumentNode* node) const override { Q_UNUSED(node); return true; }
    void enable_event(const Event& event) override { Q_UNUSED(event); }
    void disable_event(const Event& event) override { Q_UNUSED(event); }

private:
    static Autoreg<FreehandTool> autoreg;
};

class StarTool : public Tool
{
public:
    QIcon icon() const override { return QIcon::fromTheme("draw-star"); }
    QString name() const override { return QObject::tr("Star"); }
    QKeySequence key_sequence() const override { return QKeySequence(QObject::tr("*"), QKeySequence::PortableText); }
    app::settings::SettingList settings() const override { return {}; }

    void mouse_press(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_move(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_release(const MouseEvent& event) override { Q_UNUSED(event); }
    void mouse_double_click(const MouseEvent& event) override { Q_UNUSED(event); }
    void paint(const PaintEvent& event) override { Q_UNUSED(event); }
    void key_press(const KeyEvent& event) override { Q_UNUSED(event); }
    void key_release(const KeyEvent& event) override { Q_UNUSED(event); }
    QCursor cursor() override { return {}; }
    bool show_editors(model::DocumentNode* node) const override { Q_UNUSED(node); return true; }
    void enable_event(const Event& event) override { Q_UNUSED(event); }
    void disable_event(const Event& event) override { Q_UNUSED(event); }

private:
    static Autoreg<StarTool> autoreg;
};


} // namespace tools


tools::Autoreg<tools::FreehandTool> tools::FreehandTool::autoreg{tools::Registry::Draw, max_priority + 1};


tools::Autoreg<tools::StarTool> tools::StarTool::autoreg{tools::Registry::Shape, max_priority + 2};
