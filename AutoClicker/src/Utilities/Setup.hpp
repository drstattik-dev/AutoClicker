
#pragma once

#include "imgui.h"
#include "json.hpp"

#include "Style.hpp"
#include "Hotkeys.hpp"

nlohmann::json settings;


namespace Utilities
{
	void Setup()
	{
		Utilities::SetupImGuiStyles();
		
		settings = Utilities::LoadSettings();
	}
}
