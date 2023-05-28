#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Components/TitleBar.hpp"

#include "Utilities/Setup.hpp"

Walnut::Application* appRef;

class AutoClicker : public Walnut::Layer
{
public:
	virtual void OnAttach() override
	{
		Utilities::Setup();
	}
	virtual void OnUIRender() override
	{
		
		//create a window
		ImGui::Begin("AutoClicker", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);
		{

			Components::RenderTitleBar();
			

			//create a button
			if (ImGui::Button("Click"))
			{
				//click
			}
		}

		ImGui::End();
	}
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "AutoClicker";
	spec.ParentWindow = false;

	Walnut::Application* app = new Walnut::Application(spec);

	//GLFWwindow GLFWwin = app->GetWindowHandle();

	appRef = app;

	app->PushLayer<AutoClicker>();

	return app;
}