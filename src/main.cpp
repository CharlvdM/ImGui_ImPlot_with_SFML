#include "imgui-SFML.h"
#include "implot.h"
#include <SFML/Graphics.hpp>
#include <thread>

namespace {
    constexpr auto APPLICATION_NAME = "ImGui and ImPlot with SFML Demo";
    constexpr std::chrono::milliseconds WINDOW_UPDATE_SPEED {20};

    sf::Clock sDeltaClock {};
} // namespace

int main() {

    static_cast<void>(std::printf("Starting the GUI \n"));

    /// Configure the GUI window
    ImVec2 win_size {1284.0F, 1024.0F};
    sf::Vector2u windowSizeVec {static_cast<unsigned int>(win_size.x), static_cast<unsigned int>(win_size.y)};
    sf::RenderWindow window(sf::VideoMode {windowSizeVec}, "");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);
    window.setTitle(APPLICATION_NAME);

    /// Initialize SFML
    static_cast<void>(ImGui::SFML::Init(window)); // bind the ImGui library to SFML

    /// Initialize ImPlot
    ImPlot::CreateContext();

    /// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    while (window.isOpen()) {
        const auto start_time = std::chrono::high_resolution_clock::now();

        /// Sample user input using SFML
        sf::Event event {};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, sDeltaClock.restart());

        /// Demo ImPlot and ImGui
        static bool demo_imgui {true};
        static bool demo_implot {true};

        ImGui::Begin("Select Demos");
        ImGui::Checkbox("ImGui Demo", &demo_imgui);
        ImGui::Checkbox("ImPlot Demo", &demo_implot);
        ImGui::End();

        if (demo_imgui) {
            ImGui::ShowDemoWindow(&demo_imgui);
        }
        if (demo_implot) {
            ImPlot::ShowDemoWindow(&demo_implot);
        }

        /// Render the GUI using SFML
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
        std::this_thread::sleep_until(start_time + WINDOW_UPDATE_SPEED);
    }

    /// Memory cleanup
    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();

    static_cast<void>(std::printf("GUI closed \n"));
}
