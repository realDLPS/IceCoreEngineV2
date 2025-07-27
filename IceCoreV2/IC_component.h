#pragma once

#include "IC_object.h"

class IC_component : IC_object
{
	IC_component() = default;

	virtual ~IC_component() = default;

	IC_object* parent;
};