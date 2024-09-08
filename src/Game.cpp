#include "Engine.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        const mc::Engine engine(800, 600, "Minecraft");
        engine.start();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}