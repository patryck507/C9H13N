#include "memory/memory.h"
#include "globals.h"
#include "features/features.h"

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
		std::cout << "\nOpen Game";
		exit(1);
	}

	// Wait until serverbrowser.dll is loaded
	std::cout << "\nwaiting for serverbrowser.dll";
	while (!memory::module_address("serverbrowser.dll"))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	std::cout << "\nfound serverbrowser.dll";

	// Get the module addresses for client.dll and engine.dll
	memory::client = memory::module_address("client.dll");
	memory::engine = memory::module_address("engine.dll");

	// If the module addresses for client.dll and engine.dll cannot be found, print an error message
	if (!memory::client && !memory::engine)
	{
		std::cout << "\nFailed to read client.dll | engine.dll";
	}

	// If the handle to the game cannot be opened, print an error message and exit the program
	if (!memory::open_handle())
	{
		std::cout << "\nFailed to open a handle to the game";
		exit(2);
	}

	std::cout << "\nHandle Opened Successfully";

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
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	// Close the handle to the game
	memory::close_handle();

	return 0;
}
