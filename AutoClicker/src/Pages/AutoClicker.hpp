
#pragma once

#include "Walnut/Application.h"

#include <thread>

#include "../Utilities/Setup.hpp"
#include "../Utilities/ClickerUtil.hpp"
#include "../Components/TitleBar.hpp"

#include "imgui.h"

//text fields for number of clicks and delay
static char clicks[128] = "100";
static char interval[128] = "50";
int timer = 5;
//static char timerChar[128] = "5";

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

		//if start button is pressed
		if (ImGui::Button("Start"))
		{
			//wait for timer
			Utilities::WaitForTimer(timer);
			//start auto clicker
			//create new thread for auto clicker
			std::thread t1(Utilities::StartAutoClicker, clicksInt, intervalInt, std::ref(totalClicks));
			t1.detach();
		}

		//check if hotkey is pressed
		if (GetAsyncKeyState(VK_HOME))
		{
			//stop auto clicker
			Utilities::StopAutoClicker();
		}



		//sameline
		ImGui::SameLine();

		//timer countdown
		//ImGui::Text("Timer: %s", timer);

	}
};
