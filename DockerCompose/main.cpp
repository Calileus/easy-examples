#include <cstdlib>
#include <iostream>

int main()
{
    const char* greeting = std::getenv("EASYEXAMPLES_GREETING");
    std::cout << (greeting != nullptr ? greeting : "Hello from Docker Compose.") << std::endl;
    return 0;
}