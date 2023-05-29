
#pragma once

#include "Walnut/Application.h"

#include <thread>

#include "../Utilities/Setup.hpp"
#include "../Utilities/ClickerUtil.hpp"
#include "../Components/TitleBar.hpp"

#include "imgui.h"

#include "Walnut/Image.h"
#include "vulkan/vulkan.h"


//running
static bool running = false;

//text fields for number of clicks and delay
static char clicks[128] = "100";
static char interval[128] = "50";
int timer = 5;

static POINT clickTarget = { 0, 0 };
bool lookingForTarget = false;

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

		//set target position
		if (ImGui::Button("Set Target Position"))
			lookingForTarget = true;
		if (lookingForTarget)
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

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				clickTarget = mousePos;
				lookingForTarget = false;
			}
		}

		//if start button is pressed or hotkey is pressed to start auto clicker
		if (!running)
		{
			if (ImGui::Button("Start") | GetAsyncKeyState(settings["Hotkeys"]["Start"]))
			{
				running = true;

				//wait for timer
				//Utilities::WaitForTimer(timer);

				//start auto clicker
				std::thread t1(Utilities::StartAutoClicker, clicksInt, intervalInt, std::ref(totalClicks), clickTarget);
				t1.detach();
			}
		}

		//check if hotkey is pressed to stop auto clicker
		if (GetAsyncKeyState(settings["Hotkeys"]["Stop"]))
		{
			//stop auto clicker
			running = false;
			Utilities::StopAutoClicker();
		}

		ImGui::SameLine();

		//timer countdown
		//ImGui::Text("Timer: %s", timer);

	}
};
