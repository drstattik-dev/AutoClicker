#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

//Components
#include "Components/TitleBar.hpp"

//Pages
#include "Pages/AutoClicker.hpp"

//Utilities
#include "Utilities/Setup.hpp"


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.ParentWindow = false;

	Walnut::Application* app = new Walnut::Application(spec);

	appRef = app; //set appRef to app

	//SetAppRef(app); //set appRef in AutoClicker

	app->PushLayer<AutoClicker>();

	return app;
}