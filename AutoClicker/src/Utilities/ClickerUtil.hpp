
#pragma once

#include <Windows.h>
#include <thread>
#include <wingdi.h>



namespace Utilities
{
	//cancel auto clicker
	bool cancelAutoClicker = false;

	//click function
	int Click(int x = 0, int y = 0)
	{
		//send input mouse click
		INPUT input;
		input.type = INPUT_MOUSE;

		//SetCursorPos(x, y);

		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		//input.mi.dx = x;
		//input.mi.dy = y;
		SendInput(1, &input, sizeof(INPUT));

		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		//input.mi.dx = x;
		//input.mi.dy = y;
		SendInput(1, &input, sizeof(INPUT));

		return 0;
	}


	//start auto clicker
	void StartAutoClicker(int clicks, int interval, int &totalClicks, POINT Target)
	{
		cancelAutoClicker = false;

		POINT originalMousePos;
		GetCursorPos(&originalMousePos);

		//start clicking mouse
		for (int i = 0; i < clicks; i++)
		{
			//if cancel auto clicker is true
			if (cancelAutoClicker)
			{
				//stop auto clicker
				break;
			}

			//increment total clicks
			totalClicks++;

			//wait for interval
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));

			//click mouse
			Click(Target.x, Target.y);

			
		}
		//reset mouse position
		SetCursorPos(originalMousePos.x, originalMousePos.y);
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