
#pragma once

#include <Windows.h>
#include <filesystem>
#include <fstream>
#include "json.hpp"

//get current directory
static std::string currentDirectory = std::filesystem::current_path().string();

namespace Utilities
{
	//check if settings.json exists in current directory
	static bool SettingsExists()
	{
		//check if settings.json exists
		if (std::filesystem::exists(currentDirectory + "\\settings.json"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//create settings.json
	static void CreateSettings()
	{
		std::ofstream settingsFile;
		//open settings.json
		settingsFile.open(currentDirectory + "\\settings.json");

		nlohmann::json settings;
		//set default settings
		settings["Variables"]["Clicks"] = 100;
		settings["Variables"]["Interval"] = 100;
		settings["Variables"]["TotalClicks"] = 0;

		//hotkeys
		settings["Hotkeys"]["Start"] = VK_HOME;
		settings["Hotkeys"]["Stop"] = VK_END;
		

		//write settings to settings.json
		settingsFile << settings.dump(4);
		//close settings.json
		settingsFile.close();
	}

	//load settings.json
	static nlohmann::json LoadSettings()
	{
		//check if settings.json exists
		if (SettingsExists())
		{
			//open settings.json
			std::ifstream settingsFile(currentDirectory + "\\settings.json");
			nlohmann::json settings;
			//read settings.json
			settingsFile >> settings;
			//close settings.json
			settingsFile.close();
			return settings;
		}
		else
		{
			//create settings.json
			CreateSettings();
			//load settings.json
			return LoadSettings();
		}
	}
	





}