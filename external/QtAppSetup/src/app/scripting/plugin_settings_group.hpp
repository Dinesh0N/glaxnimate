#pragma once

#include "app/settings/custom_settings_group.hpp"
#include "app/widgets/plugin_settings_widget.hpp"
#include "app/scripting/plugin.hpp"

namespace app::scripting {

class PluginSettingsGroup : public app::settings::CustomSettingsGroupBase
{
public:
    PluginSettingsGroup(QStringList default_enabled)
    : enabled(std::move(default_enabled)) {}

    QString slug() const override { return "plugins"; }
    QIcon icon() const override { return QIcon::fromTheme("system-software-install"); }
    QString label() const override { return QObject::tr("Plugins"); }
    void load ( QSettings & settings ) override
    {
        PluginRegistry::instance().load();

        enabled = settings.value("enabled", enabled).toStringList();

        for ( const auto& plugin : PluginRegistry::instance().plugins() )
            if ( enabled.contains(plugin->data().id) )
                plugin->enable();
    }

    void save ( QSettings & settings ) override
    {
        enabled.clear();

        for ( const auto& plugin : PluginRegistry::instance().plugins() )
            if ( plugin->enabled() )
                enabled.push_back(plugin->data().id);

        settings.setValue("enabled", enabled);
    }

    QWidget * make_widget ( QWidget * parent ) override { return new PluginSettingsWidget(parent); }

private:
    QStringList enabled;
};

} // namespace app::scripting
