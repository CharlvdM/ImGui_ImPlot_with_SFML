#include "imgui.h"
#include "imgui-SFML.h"
#include "implot.h"
#include <SFML/Graphics.hpp>

int main() {

    static_cast<void>(std::printf("Starting the GUI \n"));

    ImVec2 main_win_size {1284.0F, 1024.0F};
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(main_win_size.x), static_cast<unsigned int>(main_win_size.y)), "",
                            sf::Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);
    ImGui::SFML::Init(window); // bind the ImGui library to SFML
    window.setTitle("ImGui and ImPlot with SFML Demo");
    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;
    ImPlot::CreateContext();

    while (window.isOpen()) {
        
    }

    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

}
