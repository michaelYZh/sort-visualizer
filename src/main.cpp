/**
 * @file main.cpp
 * @brief Entry point for the Graphical Sorting application
 * @author Original: Michael Zhang, Modernized version
 */

#include "visualization.h"
#include "ui.h"
#include "sorting_algorithms.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constants
constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768;
constexpr int DATA_SIZE = 100;

/**
 * @brief Main function
 * @return Exit code
 */
int main() {
    try {
        std::cout << "Starting Graphical Sorting application..." << std::endl;
        
        // Create the window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graphical Sorting");
        window.setFramerateLimit(60);
        
        std::cout << "Window created successfully." << std::endl;
        
        // Create visualization and UI
        Visualization visualization(window, nullptr);
        UI ui(window, visualization);
        
        // Set UI reference in visualization
        visualization.setUI(&ui);
        
        std::cout << "UI and visualization created." << std::endl;
        
        // Initialize data
        visualization.initializeData(DATA_SIZE);
        
        // Show algorithm selection screen
        ui.showAlgorithmSelection();
        
        std::cout << "Data initialized. Starting main loop..." << std::endl;
        
        // Main loop
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    std::cout << "Window close event received." << std::endl;
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        std::cout << "Escape key pressed. Closing window." << std::endl;
                        window.close();
                    }
                }
                
                // Handle UI events
                ui.handleEvent(event);
            }
            
            // Clear the window
            window.clear(sf::Color(30, 30, 30));
            
            // Draw visualization
            visualization.draw();
            
            // Draw UI
            ui.draw();
            
            // Display the window
            window.display();
        }
        
        std::cout << "Application closing normally." << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
} 