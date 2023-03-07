#include <iostream>
#include <string>

enum class LogType { LERROR, SUCCESS, INFORMATION };

void log(const LogType type, const std::string& message) {
    switch (type) {
    case LogType::LERROR:
        std::cout << "[ERROR] - " << message << std::endl;
        break;
    case LogType::SUCCESS:
        std::cout << "[SUCCESS] - " << message << std::endl;
        break;
    case LogType::INFORMATION:
        std::cout << "[INFORMATION] - " << message << std::endl;
        break;
    default:
        break;
    }
}