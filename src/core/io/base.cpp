#include "base.hpp"

QString io::ImportExport::name_filter() const
{
    QString ext_str;
    for ( const QString& ext : extensions() )
    {
        ext_str += "*." + ext + " ";
    }

    if ( ext_str.isEmpty() )
        return {};

    ext_str.resize(ext_str.size() - 1);
    //: Open/Save file dialog file filter eg: "Text files (.txt)"
    return tr("%1 (%2)").arg(name()).arg(ext_str);
}


QByteArray io::ImportExport::save(model::Document* document, const QVariantMap& setting_values, const QString& filename)
{
    QByteArray data;
    QBuffer file(&data);
    file.open(QIODevice::WriteOnly);

    QVariantMap clean_setting_values = setting_values;
    for ( const auto& setting : save_settings() )
        clean_setting_values[setting.slug] = setting.get_variant(clean_setting_values);

    if ( !save(file, filename, document, clean_setting_values) )
        return {};

    return data;
}


bool io::ImportExport::open(QIODevice& file, const QString& filename,
                    model::Document* document, const QVariantMap& setting_values)
{
    if ( !file.isOpen() && auto_open() )
        if ( !file.open(QIODevice::ReadOnly) )
            return false;

    bool ok = on_open(file, filename, document, setting_values);
    emit completed(ok);
    return ok;
}

bool io::ImportExport::save(QIODevice& file, const QString& filename,
                    model::Document* document, const QVariantMap& setting_values)
{
    if ( !file.isOpen() && auto_open() )
        if ( !file.open(QIODevice::WriteOnly) )
            return false;

    bool ok = on_save(file, filename, document, setting_values);
    emit completed(ok);
    return ok;
}

bool io::ImportExport::load(model::Document* document, const QByteArray& data,
                            const QVariantMap& setting_values, const QString& filename)
{
    if ( !document )
        return false;

    QBuffer file(const_cast<QByteArray*>(&data));
    file.open(QIODevice::ReadOnly);

    QVariantMap clean_setting_values = setting_values;
    for ( const auto& setting : open_settings() )
        clean_setting_values[setting.slug] = setting.get_variant(clean_setting_values);

    return open(file, filename, document, clean_setting_values);
}
