#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Visualization;

// Button class for UI elements
class Button {
public:
    /**
     * @brief Constructs a button with the given position, size, text, and font
     * @param position The position of the button
     * @param size The size of the button
     * @param text The text to display on the button
     * @param font The font for the button
     */
    Button(const sf::Vector2f& position, const sf::Vector2f& size, 
           const std::string& text, const sf::Font& font);
    
    /**
     * @brief Draws the button to the render window
     * @param window The render window to draw to
     */
    void draw(sf::RenderWindow& window);
    
    /**
     * @brief Sets the callback function for the button
     * @param callback The function to call when the button is clicked
     */
    void setCallback(std::function<void()> callback);
    
    /**
     * @brief Executes the callback function
     */
    void executeCallback();
    
    /**
     * @brief Handles events for the button
     * @param event The event to handle
     * @param mousePos The current mouse position
     */
    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
    
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    bool m_isHovered;
    std::function<void()> m_callback;
};

// Slider class for adjusting values
class Slider {
public:
    /**
     * @brief Constructs a slider with the given position, size, range, and font
     * @param position The position of the slider
     * @param width The width of the slider
     * @param min The minimum value of the slider
     * @param max The maximum value of the slider
     * @param label The label for the slider
     * @param font The font for the slider text
     */
    Slider(const sf::Vector2f& position, float width, float min, float max, 
           const std::string& label, const sf::Font& font);
    
    /**
     * @brief Draws the slider to the render window
     * @param window The render window to draw to
     */
    void draw(sf::RenderWindow& window);
    
    /**
     * @brief Gets the current value of the slider
     * @return The current value
     */
    float getValue() const;
    
    /**
     * @brief Sets the value of the slider
     * @param value The new value
     */
    void setValue(float value);
    
    /**
     * @brief Updates the text displaying the current value
     */
    void updateValueText();
    
    /**
     * @brief Handles a click on the slider
     * @param mousePos The position of the mouse
     */
    void handleClick(const sf::Vector2f& mousePos);
    
    /**
     * @brief Handles dragging the slider handle
     * @param mousePos The position of the mouse
     */
    void handleDrag(const sf::Vector2f& mousePos);
    
    /**
     * @brief Sets whether the slider is being dragged
     * @param dragging Whether the slider is being dragged
     */
    void setDragging(bool dragging);
    
private:
    sf::RectangleShape m_track;
    sf::RectangleShape m_handle;
    sf::Text m_label;
    sf::Text m_valueText;
    float m_min;
    float m_max;
    float m_value;
    float m_width;
    sf::Vector2f m_position;
    bool m_isDragging;
};

// Main UI class
class UI {
public:
    /**
     * @brief Constructs a UI with the given window and visualization
     * @param window Reference to the SFML window
     * @param visualization Reference to the visualization
     */
    UI(sf::RenderWindow& window, Visualization& visualization);
    
    /**
     * @brief Draws the UI to the render window
     */
    void draw();
    
    /**
     * @brief Handles events for the UI
     * @param event The event to handle
     */
    void handleEvent(const sf::Event& event);
    
    /**
     * @brief Updates the metrics display
     * @param comparisons The number of comparisons
     * @param moves The number of moves
     * @param executionTime The execution time in milliseconds
     */
    void updateMetrics(int comparisons, int moves, float executionTime);
    
    /**
     * @brief Shows the title screen
     */
    void showTitleScreen();
    
    /**
     * @brief Shows the algorithm selection screen
     */
    void showAlgorithmSelection();
    
    /**
     * @brief Shows the sorting visualization screen
     */
    void showSortingVisualization();
    
    /**
     * @brief Gets the font used by the UI
     * @return The font
     */
    const sf::Font& getFont() const;
    
    /**
     * @brief Sets the callback for the Quick Sort button
     */
    void setQuickSortCallback();
    
    /**
     * @brief Sets the callback for the Merge Sort button
     */
    void setMergeSortCallback();
    
    /**
     * @brief Sets the callback for the Insertion Sort button
     */
    void setInsertionSortCallback();
    
    /**
     * @brief Sets the callback for the Selection Sort button
     */
    void setSelectionSortCallback();
    
    /**
     * @brief Sets the callback for the Back button
     * @param callback The function to call when the button is clicked
     */
    void setBackCallback(std::function<void()> callback);
    
    /**
     * @brief Sets the callback for the Restart button
     * @param callback The function to call when the button is clicked
     */
    void setRestartCallback(std::function<void()> callback);
    
private:
    /**
     * @brief Creates the buttons for the UI
     */
    void createButtons();
    
    enum class Screen {
        TitleScreen,
        AlgorithmSelection,
        SortingVisualization
    };
    
    sf::RenderWindow& m_window;
    Visualization& m_visualization;
    sf::Font m_font;
    std::vector<Button> m_buttons;
    std::vector<Slider> m_sliders;
    sf::Text m_comparisonsText;
    sf::Text m_movesText;
    sf::Text m_timeText;
    sf::Text m_algorithmText;
    Screen m_currentScreen;
    
    // Button pointers for callback setting
    Button* m_quickSortButton;
    Button* m_mergeSortButton;
    Button* m_insertionSortButton;
    Button* m_selectionSortButton;
    Button* m_backButton;
    Button* m_restartButton;
};

#endif // UI_H 