#include "features.h"
#include "../globals.h"
#include "../game/sdk.h"

#include "../memory/memory.h"

// Create an instance of the cPlayer class for the local player
inline cPlayer LocalPlayer;

void features::legitbot::triggerbot() noexcept
{
	// Keep looping while the program is running
	while (globals::run)
	{
		// Pause the loop for 1 millisecond to prevent excessive CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// Check if the X2 mouse button is pressed and continue the loop if it's not
		if (!GetAsyncKeyState(VK_XBUTTON2))
			continue;

		// Check if the local player is alive and continue the loop if they're not
		if (!LocalPlayer.Health())
			continue;

		// Check if the local player's crosshair is pointing at an entity and continue the loop if it's not
		if (!LocalPlayer.CrosshairID() || LocalPlayer.CrosshairID() > 64)
			continue;

		// Get the target player's address using the crosshair ID
		uintptr_t TargetPlayer = memory::read<uintptr_t>(memory::client + dwEntityList + (LocalPlayer.CrosshairID() - 1) * 0x10);

		// Check if the target player is alive and continue the loop if they're not
		if (!memory::read<int32_t>(TargetPlayer + m_iHealth))
			continue;

		// Check if the target player is on the same team as the local player and continue the loop if they are
		if (memory::read<int32_t>(TargetPlayer + m_iTeamNum) == LocalPlayer.Team())
			continue;

		// If all the conditions are met, shoot at the target player
		LocalPlayer.Shoot();
	}
}
