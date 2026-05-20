#include "formatter.h"
#include <iostream>

std::string formatter(const std::string& message) {
    std::string result = "Formatter: " + message + "\n";
    std::cout << result;
    return result;
}
