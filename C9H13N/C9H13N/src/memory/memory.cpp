#include "memory.h"
#include <TlHelp32.h>

// Searches for a process with the given name and saves its ID to memory::id.
void memory::process(const std::string name) noexcept {
	auto entry = PROCESSENTRY32{ };
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// loop through processes
	do {
		if (!name.compare(entry.szExeFile)) {
			memory::id = entry.th32ProcessID;
			break;
		}
	} while (Process32Next(snap, &entry));

	// Close the snapshot handle.
	if (snap) {
		CloseHandle(snap);
	}
}

// Searches for a module with the given name and returns its base address.
std::uintptr_t memory::module_address(const std::string name) noexcept {
	auto entry = MODULEENTRY32{ };
	entry.dwSize = sizeof(MODULEENTRY32);

	const auto snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);

	std::uintptr_t addr = 0;

	// loop through modules
	do {
		if (!name.compare(entry.szModule)) {
			addr = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
			break;
		}
	} while (Module32Next(snap, &entry));

	// Close the snapshot handle.
	if (snap) {
		CloseHandle(snap);
	}

	return addr;
}

// Opens a handle to the process with the ID stored in memory::id.
// Returns true if the handle was successfully opened.
bool memory::open_handle() noexcept {
	return memory::handle = OpenProcess(PROCESS_ALL_ACCESS, 0, memory::id);
}

// Closes the handle to the process if it is open.
void memory::close_handle() noexcept {
	if (memory::handle) {
		CloseHandle(memory::handle);
	}
}
