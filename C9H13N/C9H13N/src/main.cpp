#include "memory/memory.h"
#include "globals.h"
#include "features/features.h"
#include "utils/log.h"

#include <iostream>
#include <thread>

// Function to initialize the cheat
void init()
{
	// Connect to the CSGO process
	memory::process("csgo.exe");

	// If the process ID is 0, the game is not open
	if (memory::id == 0)
	{
		log(LogType::INFORMATION, "Open Game");
		exit(1);
	}

	// Wait until serverbrowser.dll is loaded
	log(LogType::INFORMATION, "waiting for serverbrowser.dll");
	while (!memory::module_address("serverbrowser.dll"))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	log(LogType::SUCCESS, "Found serverbrowser.dll");

	// Get the module addresses for client.dll and engine.dll
	memory::client = memory::module_address("client.dll");
	memory::engine = memory::module_address("engine.dll");

	// If the module addresses for client.dll and engine.dll cannot be found, print an error message
	if (!memory::client && !memory::engine)
	{
		log(LogType::LERROR, "Failed to read client.dll | engine.dll");
	}
	log(LogType::SUCCESS, "Found client.dll and engine.dll");

	// If the handle to the game cannot be opened, print an error message and exit the program
	if (!memory::open_handle())
	{
		log(LogType::LERROR, "Failed to open a handle to the game");
		exit(2);
	}

	log(LogType::SUCCESS, "Handle created");

	// Set the run flag to true to indicate that the cheat is running
	globals::run = true;
}

// Main function
int main()
{
	// Call the init function to initialize the cheat
	init();

	// If the cheat is running, start the bhop and triggerbot threads
	if (globals::run)
	{
		std::thread{ features::misc::bhop }.detach();
		std::thread{ features::legitbot::triggerbot }.detach();
	}

	// Wait for the cheat to finish running
	while (globals::run)
	{
		if (GetAsyncKeyState(VK_HOME))
		{
			// Turn of all features
			globals::run = false;
			// Close the handle to the game
			memory::close_handle();

			log(LogType::SUCCESS, "Handle Closed, Exiting.");
			// Exit
			return 0;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
