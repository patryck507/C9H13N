#include <Windows.h>

#include <iostream>
#include <cstdint>
#include <string>

#pragma comment (lib, "ntdll.lib")

namespace memory {
    // A variable to store the process ID of the target process
    inline int id = 0;

    // A handle to the target process
    inline void* handle = nullptr;

    // Import NtReadVirtualMemory and NtWriteVirtualMemory functions from kernel32.dll
    EXTERN_C NTSTATUS NTAPI NtReadVirtualMemory(HANDLE, PVOID, PVOID, ULONG, PULONG);
    EXTERN_C NTSTATUS NTAPI NtWriteVirtualMemory(HANDLE, PVOID, PVOID, ULONG, PULONG);

    // Base addresses of the client and engine modules in the target process
    inline std::uintptr_t client = 0;
    inline std::uintptr_t engine = 0;

    // Function to obtain the process ID of a target process by name
    void process(const std::string name) noexcept;

    // Function to obtain the base address of a module in the target process by name
    std::uintptr_t module_address(const std::string name) noexcept;

    // Function to open a handle to the target process
    bool open_handle() noexcept;

    // Function to close the handle to the target process
    void close_handle() noexcept;

    // Template function to read a value from memory of the target process
    template <typename T>
    constexpr T read(const std::uintptr_t& addr) noexcept {
        T value;
        // Call NtReadVirtualMemory to read the value from the target process
        NTSTATUS status = NtReadVirtualMemory(handle, reinterpret_cast<PVOID>(addr), &value, sizeof(T), 0);
        // Basic Error Handling
        if (status != 0) {
            std::cout << "\n[MEMORY] failed to read value";
        }
        return value;
    }

    // Template function to write a value to memory of the target process
    template <typename T>
    constexpr void write(const std::uintptr_t& addr, const T& value) noexcept {
        // Call NtWriteVirtualMemory to write the value to the target process
        NTSTATUS status = NtWriteVirtualMemory(handle, reinterpret_cast<void*>(addr), const_cast<void*>(static_cast<const void*>(&value)), sizeof(T), 0);
        // Basic Error Handling
        if (status != 0) {
            std::cout << "\n[MEMORY] failed to write value";
        }
    }
}
