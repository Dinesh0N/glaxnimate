#pragma once

#include <QBuffer>

#include "io/svg/svg_parser.hpp"
#include "io/svg/svg_renderer.hpp"
#include "io/mime/mime_serializer.hpp"

namespace io::mime {

class SvgMime : public io::mime::MimeSerializer
{
public:
    QString name() const override { return QObject::tr("SVG"); }
    QStringList mime_types() const override { return {"image/svg+xml"}; }

    QByteArray serialize(const std::vector<model::DocumentNode*>& selection) const override
    {
        QByteArray data;
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        io::svg::SvgRenderer svg_rend(&buffer);
        for ( auto node : selection )
            svg_rend.write_node(node);
        svg_rend.close();
        return data;
    }

    std::vector<std::unique_ptr<model::DocumentNode>> deserialize(
        const QByteArray& data,
        model::Document* document,
        model::Composition* composition
    ) const override
    {
        QBuffer buffer(const_cast<QByteArray*>(&data));
        buffer.open(QIODevice::ReadOnly);
        try {
            return io::svg::SvgParser(&buffer, deserialize_group_mode, document, composition)
                .parse_to_objects();
        } catch ( const io::svg::SvgParseError& ) {
            return {};
        }

    }

    bool can_deserialize() const override { return true; }

    /// \todo show in settings
    io::svg::SvgParser::GroupMode deserialize_group_mode = io::svg::SvgParser::Inkscape;
};

} // namespace io::mime
