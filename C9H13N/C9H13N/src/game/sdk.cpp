#include "sdk.h"
#include "../memory/memory.h"

using namespace memory;

// Store the address of the local player object to avoid having to read it every time it's needed.
static uintptr_t cachedLocalPlayer = 0;

// Returns the address of the local player object.
uintptr_t cPlayer::LocalPlayer()
{
    // If the local player address has not yet been cached, read it from memory and store it.
    if (cachedLocalPlayer == 0)
    {
        cachedLocalPlayer = read<uintptr_t>(client + dwLocalPlayer);
    }

    // Return the cached local player address.
    return cachedLocalPlayer;
}

// Simulates a jump by writing a value to the dwForceJump offset in memory.
void cPlayer::Jump()
{
    write<int32_t>(client + dwForceJump, 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    write<int32_t>(client + dwForceJump, 4);
}

// Returns the value of the flags variable for the local player object.
int32_t cPlayer::Flags()
{
    return read<uintptr_t>(cPlayer::LocalPlayer() + m_fFlags);
}

// Returns the value of the health variable for the local player object.
int32_t cPlayer::Health()
{
    return read<int32_t>(cPlayer::LocalPlayer() + m_iHealth);
}

// Returns the value of the crosshair ID variable for the local player object.
int32_t cPlayer::CrosshairID()
{
    return read<int32_t>(cPlayer::LocalPlayer() + m_iCrosshairId);
}

// Returns the team number of the local player object.
int32_t cPlayer::Team()
{
    return read<int32_t>(cPlayer::LocalPlayer() + m_iTeamNum);
}

// Simulates shooting by writing a value to the dwForceAttack offset in memory.
void cPlayer::Shoot()
{
    write<int32_t>(client + dwForceAttack, 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    write<int32_t>(client + dwForceAttack, 4);
}
