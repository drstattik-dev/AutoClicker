
#pragma once

#include <Windows.h>
#include <thread>
#include <wingdi.h>



namespace Utilities
{
	//array of points
	POINT points[1000];
	int pointIndex = 0;

	//cancel auto clicker
	bool cancelAutoClicker = false;

	void addPoint(int x, int y)
	{
		points[pointIndex].x = x;
		points[pointIndex].y = y;
		pointIndex++;
	}

	//click function
	int Click(int x = 0, int y = 0)
	{
		//send input mouse click
		INPUT input;
		input.type = INPUT_MOUSE;

		SetCursorPos(x, y);

		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &input, sizeof(INPUT));

		input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(INPUT));

		return 0;
	}


	//start auto clicker
	void StartAutoClicker(int clicks, int interval, int &totalClicks, POINT Target, bool &running)
	{
		cancelAutoClicker = false;

		POINT originalMousePos;

		for (int i = 0; i < clicks; i++)
		{
			if (cancelAutoClicker)
				break;

			if (interval > 0)
				std::this_thread::sleep_for(std::chrono::milliseconds(interval));

			GetCursorPos(&originalMousePos);

			Click(Target.x, Target.y);

			totalClicks++;

			SetCursorPos(originalMousePos.x, originalMousePos.y);
		}

		running = false;
	}

	//stop auto clicker
	void StopAutoClicker()
	{
		cancelAutoClicker = true;
	}

	void WaitForTimer(int seconds)
	{
		for (int i = 0; i < seconds; i++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}