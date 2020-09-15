#include "detail.hpp"


const std::map<QString, QString> io::svg::detail::xmlns = {
    {"dc", "http://purl.org/dc/elements/1.1/"},
    {"cc", "http://creativecommons.org/ns#"},
    {"rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#"},
    {"svg", "http://www.w3.org/2000/svg"},
    {"sodipodi", "http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"},
    {"inkscape", "http://www.inkscape.org/namespaces/inkscape"},
    {"xlink", "http://www.w3.org/1999/xlink"},
};

const std::unordered_set<QString> io::svg::detail::css_atrrs = {
    "fill",
    "alignment-baseline",
    "baseline-shift",
    "clip-path",
    "clip-rule",
    "color",
    "color-interpolation",
    "color-interpolation-filters",
    "color-rendering",
    "cursor",
    "direction",
    "display",
    "dominant-baseline",
    "fill-opacity",
    "fill-rule",
    "filter",
    "flood-color",
    "flood-opacity",
    "font-family",
    "font-size",
    "font-size-adjust",
    "font-stretch",
    "font-style",
    "font-variant",
    "font-weight",
    "glyph-orientation-horizontal",
    "glyph-orientation-vertical",
    "image-rendering",
    "letter-spacing",
    "lighting-color",
    "marker-end",
    "marker-mid",
    "marker-start",
    "mask",
    "opacity",
    "overflow",
    "paint-order",
    "pointer-events",
    "shape-rendering",
    "stop-color",
    "stop-opacity",
    "stroke",
    "stroke-dasharray",
    "stroke-dashoffset",
    "stroke-linecap",
    "stroke-linejoin",
    "stroke-miterlimit",
    "stroke-opacity",
    "stroke-width",
    "text-anchor",
    "text-decoration",
    "text-overflow",
    "text-rendering",
    "unicode-bidi",
    "vector-effect",
    "visibility",
    "white-space",
    "word-spacing",
    "writing-mode"
};
