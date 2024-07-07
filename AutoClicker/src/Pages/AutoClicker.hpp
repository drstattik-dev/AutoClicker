
#pragma once

#include "Walnut/Application.h"

#include <thread>

#include "../Utilities/Setup.hpp"
#include "../Utilities/ClickerUtil.hpp"
#include "../Components/TitleBar.hpp"

#include "imgui.h"

#include "Walnut/Image.h"
#include "vulkan/vulkan.h"
#include <imgui_internal.h>


//running
static bool running = false;

//text fields for number of clicks and delay
static char clicks[128] = "100";
static char interval[128] = "50";
int timer = 5;

static POINT clickTarget = { 0, 0 };
bool lookingForTargets = false;

//total clicks
static int totalClicks = 0;

class AutoClicker : public Walnut::Layer
{
public:
	virtual void OnAttach() override
	{
		Utilities::Setup();
	}

	virtual void OnUIRender() override
	{
		//set size
		ImGui::SetNextWindowSize(ImVec2(500, 400));

		//create a window for auto clicker
		ImGui::Begin("Auto Clicker", nullptr, 
			ImGuiWindowFlags_NoCollapse | 
			ImGuiWindowFlags_NoDocking | 
			ImGuiWindowFlags_NoResize | 
			ImGuiWindowFlags_MenuBar | 
			ImGuiWindowFlags_NoTitleBar | 
			ImGuiWindowFlags_NoScrollbar);

		Components::RenderTitleBar();

		//render auto clicker page
		RenderAutoClickerPage();

		//end window
		ImGui::End();
	}

private:
	void RenderAutoClickerPage()
	{

		//render text fields
		ImGui::InputText("Number of clicks", clicks, IM_ARRAYSIZE(clicks));
		ImGui::InputText("Interval", interval, IM_ARRAYSIZE(interval));

		//convert int to char array
		//sprintf_s(timerChar, "%d", timer);

		//render timer before start input
		//ImGui::InputText("Timer", timerChar, IM_ARRAYSIZE(timerChar));


		//render total clicks
		ImGui::Text("Total clicks: %d", totalClicks);

		//convert text fields to ints
		int clicksInt = atoi(clicks);
		int intervalInt = atoi(interval);
		//if lookingForTarget true disable the button
		//set target position
		if (ImGui::Button("Set Target Position"))
			lookingForTargets = !lookingForTargets;

		if (lookingForTargets && !ImGui::IsAnyItemHovered())
		{

			POINT mousePos;
			GetCursorPos(&mousePos);
			std::string mousePosString = "MouseX: " + std::to_string(mousePos.x) + ", MouseY: " + std::to_string(mousePos.y);

			//show text next to mouse
			ImGui::SetNextWindowPos(ImVec2(mousePos.x + 10, mousePos.y + 10));

			//set box size to text size
			ImVec2 textSize = ImVec2(ImGui::CalcTextSize(mousePosString.c_str()));

			textSize.x += 10;
			ImGui::SetNextWindowSize(textSize);

			ImGui::Begin("Target Position", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
			ImGui::Text("MouseX: %d, MouseY: %d", mousePos.x, mousePos.y);
			ImGui::End();

			//check if hovering over the 

			if (GetAsyncKeyState(VK_LBUTTON))
			{	
				Utilities::addPoint(mousePos.x, mousePos.y);
				clickTarget = mousePos;
			}
		}

		//if start button is pressed or hotkey is pressed to start auto clicker
		if (ImGui::Button(!running ? "Start" : "Stop") || GetAsyncKeyState(settings["Hotkeys"][!running ? "Start" : "Stop"]))
		{
			running = !running;

			if (!running)
			{
				Utilities::StopAutoClicker();
				return;
			}
			else
			{

				std::thread t1(Utilities::StartAutoClicker, clicksInt, intervalInt, std::ref(totalClicks), clickTarget, std::ref(running));
				t1.detach();
			}
		}

		ImGui::SameLine();

		//timer countdown
		//ImGui::Text("Timer: %s", timer);

	}
};
