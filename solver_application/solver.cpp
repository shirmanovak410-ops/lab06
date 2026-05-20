#include <iostream>
#include "formatter_ex.h"
#include "solver.h"

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;

    std::cin >> a >> b >> c;

    float x1 = 0;
    float x2 = 0;

    try
    {
        solve(a, b, c, x1, x2);

        formatter_ex("x1 = " + std::to_string(x1));
        formatter_ex("x2 = " + std::to_string(x2));
    }
    catch (const std::logic_error& ex)
    {
        formatter_ex(ex.what());
    }

    return 0;
}
