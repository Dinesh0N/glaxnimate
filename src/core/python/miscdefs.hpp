#pragma once

#include "app/scripting/python/register_machinery.hpp"

static constexpr auto no_own = py::return_value_policy::automatic_reference;

using namespace app::scripting::python;

void define_utils(py::module& m);

void define_log(py::module& m);

py::module define_detail(py::module& parent);

void define_environment(py::module& glaxnimate_module);
