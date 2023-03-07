#include "features.h"
#include "../globals.h"
#include "../game/sdk.h"

// Create an instance of the cPlayer class for the local player
inline cPlayer LocalPlayer;

void features::misc::bhop() noexcept
{
	// Keep looping while the program is running
	while (globals::run)
	{
		// Pause the loop for 1 millisecond to prevent excessive CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// Check if the Space button is pressed and continue the loop if it's not
		if (!GetAsyncKeyState(VK_SPACE))
			continue;

		// Check if the local player is alive and continue the loop if they're not
		if (!LocalPlayer.Health())
			continue;

		// Check if the local player is on the ground, If on the ground, make the local player jump
		if (LocalPlayer.Flags() & (1 << 0))
			LocalPlayer.Jump();		
	}
}