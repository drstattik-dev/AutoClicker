
#pragma once

#include <Windows.h>
#include <thread>




namespace Utilities
{
	//cancel auto clicker
	bool cancelAutoClicker = false;

	//click function
	void Click(int x = 0, int y = 0)
	{
		//send input mouse click
		INPUT input;
		input.type = INPUT_MOUSE;

		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));

		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));
	}


	//start auto clicker
	void StartAutoClicker(int clicks, int interval, int &totalClicks)
	{
		cancelAutoClicker = false;

		//start clicking mouse
		for (int i = 0; i < clicks; i++)
		{
			//if cancel auto clicker is true
			if (cancelAutoClicker)
			{
				//stop auto clicker
				break;
			}

			//wait for interval using thread
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));

			//increment total clicks
			totalClicks++;

			Click();
			
		}
	}

	//stop auto clicker
	void StopAutoClicker()
	{
		cancelAutoClicker = true;
	}

	//timer
	void WaitForTimer(int seconds)
	{
		//start timer
		for (int i = 0; i < seconds; i++)
		{
			//wait for 1 second
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}