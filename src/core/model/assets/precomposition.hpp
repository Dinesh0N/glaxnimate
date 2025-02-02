/*
 * SPDX-FileCopyrightText: 2019-2023 Mattia Basaglia <dev@dragon.best>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "asset.hpp"
#include "model/composition.hpp"

namespace glaxnimate::model {

class Precomposition : public Composition, public AssetBase
{
    GLAXNIMATE_OBJECT(Precomposition)

public:
    using Composition::Composition;

    QIcon tree_icon() const override;
    QString type_name_human() const override;
    bool remove_if_unused(bool clean_lists) override;
    DocumentNode* docnode_parent() const override;

};

} // namespace glaxnimate::model

