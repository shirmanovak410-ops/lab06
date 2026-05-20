#include "formatter_ex.h"
#include "formatter.h"
#include <iostream>

void formatter_ex(const std::string& message) {
    std::string formatted = formatter(message);
    std::cout << formatted;
}
