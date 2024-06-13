#pragma once
#include <Windows.h>
#include <windef.h>
#include <bitset>

namespace CommonUtilities
{
	class Input
	{
	public:
		Input() = default;
		~Input() = default;

		void Update();
		void SetMousePosision(int aXpos, int aYpos);
		void SetMouseWindowPosision(int aXpos, int aYpos);
		void LockCursor(bool aSwitch);

		bool UpdateEvents(UINT aMsg, WPARAM aWparam, LPARAM aLparam);
		bool GetKeyDown(int aKeyCode);
		bool GetKeyUp(int aKeyCode);
		bool GetKeyPressed(int aKeyCode);

		POINT GetMousePosision();
		POINT GetMouseDelta();
		int GetMouseWheelDelta();

	private:
		std::bitset<256> myDownKey{};
		std::bitset<256> myCurrentKey{};
		std::bitset<256> myUpKey{};

		POINT myCurrentMousePosision{ 0, 0 };
		POINT myPreviusMousePosision{ 0, 0 };
		POINT myDeltaMousePosision{ 0, 0 };

		int myWheelDelta = {};
	};
}