#include "Engine.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        const mc::Engine engine(1260, 720, "Minecraft");
        engine.start();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}