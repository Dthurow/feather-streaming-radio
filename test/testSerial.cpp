#include "testSerial.h"
#include <iostream>

void testSerial::println(const char *message)
{
    std::cout << message;
    std::cout << "\n";
}

void testSerial::println(char message)
{
    std::cout << message;
    std::cout << "\n";
}

void testSerial::println(int message)
{
    std::cout << message;
    std::cout << "\n";
}

void testSerial::print(const char *message)
{
    std::cout << message;
}

void testSerial::print(int message)
{
    std::cout << message;
}
