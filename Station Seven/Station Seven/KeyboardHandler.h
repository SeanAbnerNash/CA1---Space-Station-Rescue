#pragma once
class KeyboardHandler
{
	struct GamePadState
	{
		bool A{ false };
		bool B{ false };
		bool X{ false };
		bool Y{ false };
		bool LB{ false };
		bool RB{ false };
		bool LeftThumbStickClick{ false };
		bool RightThumbStickClick{ false };
		bool DpadUp{ false };
		bool DpadDown{ false };
		bool DpadLeft{ false };
		bool DpadRight{ false };
		bool Start{ false };
		bool Back{ false };
		bool Xbox{ false };
		float RTrigger{ 0 };
		float LTrigger{ 0 };

		float leftAngleRAD;
		float rightAngleRAD;

		float leftAngleDEG;
		float rightAngleDEG;
	};
};

