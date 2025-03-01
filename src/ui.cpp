/**
 * @file UI.cpp
 * @brief Implementation of the UI class
 */

#include "ui.h"
#include "visualization.h"
#include "sorting_algorithms.h"
#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * @brief Constructor for Button
 * @param position The position of the button
 * @param size The size of the button
 * @param text The text to display on the button
 * @param font The font for the button
 */
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text, const sf::Font& font)
    : m_position(position), m_size(size), m_isHovered(false), m_callback(nullptr) {
    // Create button shape with rounded corners
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(50, 50, 50)); // Dark gray background
    m_shape.setOutlineThickness(1.0f);
    m_shape.setOutlineColor(sf::Color(100, 100, 100)); // Light gray outline
    
    // Set up text
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(14); // Smaller text size
    m_text.setFillColor(sf::Color(255, 255, 255)); // Pure white text color
    
    // Center text in button
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setPosition(
        position.x + (size.x - textBounds.width) / 2.0f - textBounds.left,
        position.y + (size.y - textBounds.height) / 2.0f - textBounds.top
    );
}

/**
 * @brief Draw the button to the render window
 * @param window The render window to draw to
 */
void Button::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
    
    // Only draw text if the font is valid
    try {
        window.draw(m_text);
    } catch (const std::exception& e) {
        // If text drawing fails, draw a colored rectangle in the center of the button
        sf::RectangleShape indicator(sf::Vector2f(m_size.x * 0.6f, m_size.y * 0.4f));
        indicator.setPosition(
            m_position.x + (m_size.x - indicator.getSize().x) / 2.0f,
            m_position.y + (m_size.y - indicator.getSize().y) / 2.0f
        );
        indicator.setFillColor(sf::Color(255, 255, 255));
        window.draw(indicator);
    }
}

/**
 * @brief Set the callback function for the button
 * @param callback The function to call when the button is clicked
 */
void Button::setCallback(std::function<void()> callback) {
    m_callback = callback;
}

/**
 * @brief Execute the callback function
 */
void Button::executeCallback() {
    if (m_callback) {
        m_callback();
    }
}

/**
 * @brief Handle events for the button
 * @param event The event to handle
 * @param mousePos The current mouse position
 */
void Button::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos) {
    bool wasHovered = m_isHovered;
    m_isHovered = (mousePos.x >= m_position.x && mousePos.x <= m_position.x + m_size.x &&
                  mousePos.y >= m_position.y && mousePos.y <= m_position.y + m_size.y);
    
    // Update button appearance based on hover state
    if (m_isHovered && !wasHovered) {
        // Mouse entered the button
        m_shape.setFillColor(sf::Color(70, 70, 70)); // Lighter gray when hovered
    } else if (!m_isHovered && wasHovered) {
        // Mouse left the button
        m_shape.setFillColor(sf::Color(50, 50, 50)); // Back to normal color
    }
    
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left && 
        m_isHovered) {
        // Button clicked - change color briefly
        m_shape.setFillColor(sf::Color(100, 100, 100)); // Even lighter when clicked
        executeCallback();
    } else if (event.type == sf::Event::MouseButtonReleased && 
               event.mouseButton.button == sf::Mouse::Left && 
               m_isHovered) {
        // Button released - return to hover color
        m_shape.setFillColor(sf::Color(70, 70, 70));
    }
}

/**
 * @brief Constructor for Slider
 * @param position The position of the slider
 * @param width The width of the slider
 * @param min The minimum value of the slider
 * @param max The maximum value of the slider
 * @param label The label for the slider
 * @param font The font for the slider
 */
Slider::Slider(const sf::Vector2f& position, float width, float min, float max, 
                 const std::string& label, const sf::Font& font)
    : m_min(min), m_max(max), m_value(100.0f), m_width(width), 
      m_position(position), m_isDragging(false) {
    // Create track
    m_track.setPosition(position);
    m_track.setSize(sf::Vector2f(width, 4.0f));
    m_track.setFillColor(sf::Color(80, 80, 80));
    m_track.setOutlineColor(sf::Color(100, 100, 100));
    m_track.setOutlineThickness(1.0f);
    
    // Create handle
    const float handleWidth = 10.0f;
    const float handleHeight = 16.0f;
    float handleX = position.x + (m_value - m_min) / (m_max - m_min) * width - handleWidth / 2.0f;
    m_handle.setPosition(sf::Vector2f(handleX, position.y - (handleHeight - 4.0f) / 2.0f));
    m_handle.setSize(sf::Vector2f(handleWidth, handleHeight));
    m_handle.setFillColor(sf::Color(120, 120, 120));
    m_handle.setOutlineColor(sf::Color(150, 150, 150));
    m_handle.setOutlineThickness(1.0f);
    
    // Create label
    m_label.setFont(font);
    m_label.setString(label);
    m_label.setCharacterSize(14);
    m_label.setFillColor(sf::Color(220, 220, 220));
    m_label.setPosition(position.x, position.y - 25.0f);
    
    // Create value text
    m_valueText.setFont(font);
    m_valueText.setCharacterSize(12);
    m_valueText.setFillColor(sf::Color(200, 200, 200));
    updateValueText();
    m_valueText.setPosition(position.x + width + 10.0f, position.y - 5.0f);
}

/**
 * @brief Draw the slider to the render window
 * @param window The render window to draw to
 */
void Slider::draw(sf::RenderWindow& window) {
    window.draw(m_track);
    window.draw(m_handle);
    
    // Only draw text if the font is valid
    try {
        window.draw(m_label);
        window.draw(m_valueText);
    } catch (const std::exception& e) {
        // If text drawing fails, draw colored rectangles instead
        sf::RectangleShape labelIndicator(sf::Vector2f(40.0f, 10.0f));
        labelIndicator.setPosition(m_position.x, m_position.y - 20.0f);
        labelIndicator.setFillColor(sf::Color(255, 255, 255));
        window.draw(labelIndicator);
        
        sf::RectangleShape valueIndicator(sf::Vector2f(20.0f, 10.0f));
        valueIndicator.setPosition(m_position.x + m_width + 10.0f, m_position.y - 5.0f);
        valueIndicator.setFillColor(sf::Color(255, 255, 255));
        window.draw(valueIndicator);
    }
}

/**
 * @brief Get the current value of the slider
 * @return The current value
 */
float Slider::getValue() const {
    return m_value;
}

/**
 * @brief Set the value of the slider
 * @param value The new value
 */
void Slider::setValue(float value) {
    m_value = std::max(m_min, std::min(m_max, value));
    
    // Update handle position
    float handleX = m_position.x + (m_value - m_min) / (m_max - m_min) * m_width - m_handle.getSize().x / 2.0f;
    m_handle.setPosition(sf::Vector2f(handleX, m_handle.getPosition().y));
    
    updateValueText();
}

/**
 * @brief Update the text displaying the current value
 */
void Slider::updateValueText() {
    // Format value with 0 decimal places
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << m_value;
    m_valueText.setString(ss.str());
}

/**
 * @brief Handle click event for the slider
 * @param mousePos The position of the mouse
 */
void Slider::handleClick(const sf::Vector2f& mousePos) {
    // Check if mouse is over handle
    sf::FloatRect handleBounds = m_handle.getGlobalBounds();
    if (handleBounds.contains(mousePos)) {
        m_isDragging = true;
        return;
    }
    
    // Check if mouse is over track
    sf::FloatRect trackBounds = m_track.getGlobalBounds();
    if (trackBounds.contains(mousePos)) {
        // Set handle position to mouse position
        float newValue = m_min + (mousePos.x - m_position.x) / m_width * (m_max - m_min);
        setValue(newValue);
        m_isDragging = true;
    }
}

/**
 * @brief Handle drag event for the slider
 * @param mousePos The position of the mouse
 */
void Slider::handleDrag(const sf::Vector2f& mousePos) {
    if (m_isDragging) {
        // Update value based on mouse position
        float newValue = m_min + (mousePos.x - m_position.x) / m_width * (m_max - m_min);
        setValue(newValue);
    }
}

/**
 * @brief Set the dragging state of the slider
 * @param dragging True if the slider is being dragged, false otherwise
 */
void Slider::setDragging(bool dragging) {
    m_isDragging = dragging;
}

/**
 * @brief Constructor for UI
 * @param window Reference to the SFML window
 * @param visualization Reference to the visualization
 */
UI::UI(sf::RenderWindow& window, Visualization& visualization)
    : m_window(window), m_visualization(visualization), m_currentScreen(Screen::TitleScreen) {
    // Try to load system fonts first
    bool fontLoaded = false;
    
    // Try common system fonts on macOS
    const std::vector<std::string> systemFonts = {
        // macOS system fonts
        "/System/Library/Fonts/SFNS.ttf",
        "/System/Library/Fonts/SFNSText.ttf",
        "/System/Library/Fonts/SF-Pro.ttf",
        "/System/Library/Fonts/SFNSDisplay.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/System/Library/Fonts/HelveticaNeue.ttc",
        "/Library/Fonts/Arial.ttf",
        "/Library/Fonts/Arial Unicode.ttf",
        // Linux system fonts
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        // Windows system fonts (if running in compatibility layer)
        "C:/Windows/Fonts/arial.ttf",
        // Fallback to bundled font
        "asset/OpenSans-Regular.ttf"
    };
    
    for (const auto& fontPath : systemFonts) {
        if (m_font.loadFromFile(fontPath)) {
            fontLoaded = true;
            std::cout << "Loaded font successfully from: " << fontPath << std::endl;
            break;
        }
    }
    
    // If no font was loaded, use a fallback approach
    if (!fontLoaded) {
        std::cerr << "Failed to load any font. Using fallback approach." << std::endl;
        // Continue without a font - we'll use colored rectangles instead of text
    }
    
    // Initialize metrics text
    m_algorithmText.setFont(m_font);
    m_algorithmText.setCharacterSize(14);
    m_algorithmText.setFillColor(sf::Color(255, 255, 255));
    m_algorithmText.setPosition(m_window.getSize().x - 200.0f, 10.0f);
    m_algorithmText.setString("Algorithm: None");
    
    m_comparisonsText.setFont(m_font);
    m_comparisonsText.setCharacterSize(12);
    m_comparisonsText.setFillColor(sf::Color(255, 255, 255));
    m_comparisonsText.setPosition(m_window.getSize().x - 200.0f, 35.0f);
    m_comparisonsText.setString("Comparisons: 0");
    
    m_movesText.setFont(m_font);
    m_movesText.setCharacterSize(12);
    m_movesText.setFillColor(sf::Color(255, 255, 255));
    m_movesText.setPosition(m_window.getSize().x - 200.0f, 55.0f);
    m_movesText.setString("Swaps: 0");
    
    m_timeText.setFont(m_font);
    m_timeText.setCharacterSize(12);
    m_timeText.setFillColor(sf::Color(255, 255, 255));
    m_timeText.setPosition(m_window.getSize().x - 200.0f, 75.0f);
    m_timeText.setString("Time: 0.00 ms");
    
    // Create array size slider - moved to top of screen
    Slider arraySizeSlider(
        sf::Vector2f(150.0f, 40.0f), // Adjusted position to be fully visible
        200.0f,
        30.0f,  // Minimum value changed from 10 to 30
        300.0f, // Maximum value changed from 200 to 300
        "Array Size",
        m_font
    );
    m_sliders.push_back(arraySizeSlider);
    
    // Create buttons
    createButtons();
    
    // Set initial screen
    showTitleScreen();
}

/**
 * @brief Draw the UI
 */
void UI::draw() {
    // Draw buttons
    for (auto& button : m_buttons) {
        button.draw(m_window);
    }
    
    // Draw sliders
    for (auto& slider : m_sliders) {
        slider.draw(m_window);
    }
    
    // Draw metrics text if on sorting visualization screen
    if (m_currentScreen == Screen::SortingVisualization) {
        try {
            m_window.draw(m_algorithmText);
            m_window.draw(m_comparisonsText);
            m_window.draw(m_movesText);
            m_window.draw(m_timeText);
        } catch (const std::exception& e) {
            // If text drawing fails, draw colored rectangles instead
            sf::RectangleShape algorithmIndicator(sf::Vector2f(100.0f, 10.0f));
            algorithmIndicator.setPosition(m_window.getSize().x - 200.0f, 10.0f);
            algorithmIndicator.setFillColor(sf::Color(255, 255, 255));
            m_window.draw(algorithmIndicator);
            
            sf::RectangleShape comparisonsIndicator(sf::Vector2f(80.0f, 8.0f));
            comparisonsIndicator.setPosition(m_window.getSize().x - 200.0f, 35.0f);
            comparisonsIndicator.setFillColor(sf::Color(255, 255, 255));
            m_window.draw(comparisonsIndicator);
            
            sf::RectangleShape movesIndicator(sf::Vector2f(80.0f, 8.0f));
            movesIndicator.setPosition(m_window.getSize().x - 200.0f, 55.0f);
            movesIndicator.setFillColor(sf::Color(255, 255, 255));
            m_window.draw(movesIndicator);
            
            sf::RectangleShape timeIndicator(sf::Vector2f(80.0f, 8.0f));
            timeIndicator.setPosition(m_window.getSize().x - 200.0f, 75.0f);
            timeIndicator.setFillColor(sf::Color(255, 255, 255));
            m_window.draw(timeIndicator);
        }
    }
}

/**
 * @brief Handle events for the UI
 * @param event The event to handle
 */
void UI::handleEvent(const sf::Event& event) {
    // Convert mouse position to world coordinates
    sf::Vector2i pixelPos;
    if (event.type == sf::Event::MouseMoved) {
        pixelPos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
    } else if (event.type == sf::Event::MouseButtonPressed || 
               event.type == sf::Event::MouseButtonReleased) {
        pixelPos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
    }
    sf::Vector2f mousePos = m_window.mapPixelToCoords(pixelPos);
    
    // Handle button events
    for (auto& button : m_buttons) {
        button.handleEvent(event, mousePos);
    }
    
    // Handle slider events
    for (auto& slider : m_sliders) {
        if (event.type == sf::Event::MouseButtonPressed && 
            event.mouseButton.button == sf::Mouse::Left) {
            slider.handleClick(mousePos);
        } else if (event.type == sf::Event::MouseButtonReleased && 
                  event.mouseButton.button == sf::Mouse::Left) {
            slider.setDragging(false);
            
            // If this is the array size slider, reinitialize data with new size
            if (&slider == &m_sliders[0]) {
                m_visualization.initializeData(static_cast<int>(slider.getValue()));
            }
        } else if (event.type == sf::Event::MouseMoved) {
            slider.handleDrag(mousePos);
        }
    }
}

/**
 * @brief Update the metrics display
 * @param comparisons The number of comparisons
 * @param moves The number of moves
 * @param executionTime The execution time in milliseconds
 */
void UI::updateMetrics(int comparisons, int moves, float executionTime) {
    std::stringstream ss;
    
    ss.str("");
    ss << "Comparisons: " << std::setw(8) << comparisons;
    m_comparisonsText.setString(ss.str());
    
    ss.str("");
    ss << "Swaps:       " << std::setw(8) << moves;
    m_movesText.setString(ss.str());
    
    ss.str("");
    ss << "Time:        " << std::setw(8) << std::fixed << std::setprecision(2) << executionTime << " ms";
    m_timeText.setString(ss.str());
}

/**
 * @brief Show the title screen
 */
void UI::showTitleScreen() {
    m_currentScreen = Screen::TitleScreen;
    
    // Hide all buttons except the "Start" button (using the first button as Start)
    for (size_t i = 0; i < m_buttons.size(); ++i) {
        if (i == 0) { // First button becomes "Start"
            m_buttons[i].setCallback([this]() {
                showAlgorithmSelection();
            });
        }
    }
}

/**
 * @brief Show the algorithm selection screen
 */
void UI::showAlgorithmSelection() {
    m_currentScreen = Screen::AlgorithmSelection;
    
    // Set up the algorithm selection buttons
    setQuickSortCallback();
    setMergeSortCallback();
    setInsertionSortCallback();
    setSelectionSortCallback();
    
    // Set up back button to go to title screen
    setBackCallback([this]() {
        showTitleScreen();
    });
    
    // Set up restart button to reset data
    setRestartCallback([this]() {
        m_visualization.resetData();
    });
}

/**
 * @brief Show the sorting visualization screen
 */
void UI::showSortingVisualization() {
    m_currentScreen = Screen::SortingVisualization;
    
    // Set up back button to go to algorithm selection
    setBackCallback([this]() {
        showAlgorithmSelection();
    });
    
    // Set up restart button to reset data
    setRestartCallback([this]() {
        m_visualization.resetData();
    });
}

/**
 * @brief Get the font used by the UI
 * @return The font
 */
const sf::Font& UI::getFont() const {
    return m_font;
}

/**
 * @brief Set the callback for the Quick Sort button
 */
void UI::setQuickSortCallback() {
    if (m_quickSortButton) {
        m_quickSortButton->setCallback([this]() {
            m_currentScreen = Screen::SortingVisualization;
            m_algorithmText.setString("Quick Sort");
            m_visualization.restoreOriginalData(); // Restore original unsorted data
            SortingAlgorithms sorter(m_visualization);
            sorter.quickSort();
        });
    }
}

/**
 * @brief Set the callback for the Merge Sort button
 */
void UI::setMergeSortCallback() {
    if (m_mergeSortButton) {
        m_mergeSortButton->setCallback([this]() {
            m_currentScreen = Screen::SortingVisualization;
            m_algorithmText.setString("Merge Sort");
            m_visualization.restoreOriginalData(); // Restore original unsorted data
            SortingAlgorithms sorter(m_visualization);
            sorter.mergeSort();
        });
    }
}

/**
 * @brief Set the callback for the Insertion Sort button
 */
void UI::setInsertionSortCallback() {
    if (m_insertionSortButton) {
        m_insertionSortButton->setCallback([this]() {
            m_currentScreen = Screen::SortingVisualization;
            m_algorithmText.setString("Insertion Sort");
            m_visualization.restoreOriginalData(); // Restore original unsorted data
            SortingAlgorithms sorter(m_visualization);
            sorter.insertionSort();
        });
    }
}

/**
 * @brief Set the callback for the Selection Sort button
 */
void UI::setSelectionSortCallback() {
    if (m_selectionSortButton) {
        m_selectionSortButton->setCallback([this]() {
            m_currentScreen = Screen::SortingVisualization;
            m_algorithmText.setString("Selection Sort");
            m_visualization.restoreOriginalData(); // Restore original unsorted data
            SortingAlgorithms sorter(m_visualization);
            sorter.selectionSort();
        });
    }
}

/**
 * @brief Set the callback for the Back button
 * @param callback The function to call when the button is clicked
 */
void UI::setBackCallback(std::function<void()> callback) {
    if (m_backButton) {
        m_backButton->setCallback(callback);
    }
}

/**
 * @brief Set the callback for the Restart button
 * @param callback The function to call when the button is clicked
 */
void UI::setRestartCallback(std::function<void()> callback) {
    if (m_restartButton) {
        m_restartButton->setCallback(callback);
    }
}

/**
 * @brief Create the buttons for the UI
 */
void UI::createButtons() {
    const float buttonWidth = 120.0f; // Smaller width
    const float buttonHeight = 30.0f; // Smaller height
    const float buttonSpacing = 15.0f; // Slightly reduced spacing
    const float startX = (m_window.getSize().x - (4 * buttonWidth + 3 * buttonSpacing)) / 2.0f; // Center horizontally
    const float startY = 110.0f; // Position lower on screen to avoid overlap
    
    // Quick Sort button
    Button quickSortButton(
        sf::Vector2f(startX, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Quick Sort",
        m_font
    );
    quickSortButton.setCallback([this]() {
        m_currentScreen = Screen::SortingVisualization;
        m_algorithmText.setString("Quick Sort");
        m_visualization.restoreOriginalData(); // Restore original unsorted data
        SortingAlgorithms sorter(m_visualization);
        sorter.quickSort();
    });
    m_buttons.push_back(quickSortButton);
    
    // Merge Sort button
    Button mergeSortButton(
        sf::Vector2f(startX + buttonWidth + buttonSpacing, startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Merge Sort",
        m_font
    );
    mergeSortButton.setCallback([this]() {
        m_currentScreen = Screen::SortingVisualization;
        m_algorithmText.setString("Merge Sort");
        m_visualization.restoreOriginalData(); // Restore original unsorted data
        SortingAlgorithms sorter(m_visualization);
        sorter.mergeSort();
    });
    m_buttons.push_back(mergeSortButton);
    
    // Insertion Sort button
    Button insertionSortButton(
        sf::Vector2f(startX + 2 * (buttonWidth + buttonSpacing), startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Insertion Sort",
        m_font
    );
    insertionSortButton.setCallback([this]() {
        m_currentScreen = Screen::SortingVisualization;
        m_algorithmText.setString("Insertion Sort");
        m_visualization.restoreOriginalData(); // Restore original unsorted data
        SortingAlgorithms sorter(m_visualization);
        sorter.insertionSort();
    });
    m_buttons.push_back(insertionSortButton);
    
    // Selection Sort button
    Button selectionSortButton(
        sf::Vector2f(startX + 3 * (buttonWidth + buttonSpacing), startY),
        sf::Vector2f(buttonWidth, buttonHeight),
        "Selection Sort",
        m_font
    );
    selectionSortButton.setCallback([this]() {
        m_currentScreen = Screen::SortingVisualization;
        m_algorithmText.setString("Selection Sort");
        m_visualization.restoreOriginalData(); // Restore original unsorted data
        SortingAlgorithms sorter(m_visualization);
        sorter.selectionSort();
    });
    m_buttons.push_back(selectionSortButton);
    
    // Back button (top left corner)
    Button backButton(
        sf::Vector2f(20.0f, 20.0f),
        sf::Vector2f(80.0f, 30.0f),
        "Back",
        m_font
    );
    backButton.setCallback([this]() {
        showAlgorithmSelection();
    });
    m_buttons.push_back(backButton);
    
    // Restart button (top left, below back button)
    Button restartButton(
        sf::Vector2f(20.0f, 60.0f),
        sf::Vector2f(80.0f, 30.0f),
        "Restart",
        m_font
    );
    restartButton.setCallback([this]() {
        m_visualization.resetData();
    });
    m_buttons.push_back(restartButton);
    
    // Store pointers to buttons for callback setting
    m_quickSortButton = &m_buttons[0];
    m_mergeSortButton = &m_buttons[1];
    m_insertionSortButton = &m_buttons[2];
    m_selectionSortButton = &m_buttons[3];
    m_backButton = &m_buttons[4];
    m_restartButton = &m_buttons[5];
} 