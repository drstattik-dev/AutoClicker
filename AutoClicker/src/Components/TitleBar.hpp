
#pragma once

#include <iostream>

#include "Walnut/EntryPoint.h"
#include "Walnut/Application.h"

#include "imgui.h"

Walnut::Application* appRef;

namespace Components
{
	void RenderTitleBar()
	{
		std::cout << "RenderUI" << std::endl;
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File", true))
			{
				if (ImGui::MenuItem("Exit"))
				{
					
					appRef->Close();
				}
				ImGui::EndMenu();
			}

			//Minimize button
			{

				ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 48);

				if (ImGui::BeginMenu("_", false))
				{
					//std::cout << "Minimize" << std::endl;
					ImGui::EndMenu();
				}

			}

			//exit button
			{
				ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 24);

				if (ImGui::BeginMenu("X", true))
				{
					appRef->Close();
					ImGui::EndMenu();
				}
			}

			ImGui::EndMenuBar();
		}
	}
};



