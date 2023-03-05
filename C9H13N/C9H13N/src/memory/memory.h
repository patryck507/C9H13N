#include <Windows.h>

#include <cstdint>
#include <string>

namespace memory {
    // A variable to store the process ID of the target process
    inline int id = 0;

    // A handle to the target process
    inline void* handle = nullptr;

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

    // Templated function to read a value of type T from the target process at the specified address
    template <typename T>
    constexpr T read(const std::uintptr_t& addr) noexcept {
        // Create a variable to store the value read from the target process
        T value;
        // Use the Windows API function ReadProcessMemory to read the value from the target process
        // The handle to the target process is stored in the 'handle' variable
        // The address to read from is passed as a parameter
        // The size of the value to read is determined using sizeof(T)
        ReadProcessMemory(handle, reinterpret_cast<const void*>(addr), &value, sizeof(T), 0);
        // Return the value read from the target process
        return value;
    }

    // Templated function to write a value of type T to the target process at the specified address
    template <typename T>
    constexpr void write(const std::uintptr_t& addr, const T& value) noexcept {
        // Use the Windows API function WriteProcessMemory to write the value to the target process
        // The handle to the target process is stored in the 'handle' variable
        // The address to write to is passed as a parameter
        // The size of the value to write is determined using sizeof(T)
        WriteProcessMemory(handle, reinterpret_cast<void*>(addr), &value, sizeof(T), 0);
    }
}
