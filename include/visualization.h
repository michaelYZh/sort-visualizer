#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

// Forward declarations
class UI;

class Visualization {
public:
    Visualization(sf::RenderWindow& window, UI* ui);
    ~Visualization() = default;

    // Initialize the data array with random values
    void initializeData(int size);
    
    // Reset the data array
    void resetData();
    
    // Restore the original unsorted data
    void restoreOriginalData();
    
    // Draw the current state of the data
    void draw();
    
    // Get the data array
    const std::vector<int>& getData() const;
    
    // Set the data array
    void setData(const std::vector<int>& data);
    
    /**
     * @brief Update the visualization with new data and metrics
     * @param data The data to visualize
     * @param comparisons The number of comparisons
     * @param moves The number of moves
     * @param executionTime The execution time in milliseconds
     */
    void updateVisualization(const std::vector<int>& data, int comparisons, int moves, float executionTime = 0.0f);
    
    // Highlight specific elements (e.g., elements being compared)
    void highlightElements(int index1, int index2);
    
    // Set the index up to which elements are sorted
    void setSortedUpToIndex(int index);
    
    // Set the algorithm name for display
    void setAlgorithmName(const std::string& name);
    
    // Get window dimensions
    sf::Vector2u getWindowSize() const;
    
    // Get metrics
    int getComparisons() const;
    int getMoves() const;
    
    // Reset metrics
    void resetMetrics();
    
    // Set the UI reference
    void setUI(UI* ui);

private:
    sf::RenderWindow& m_window;
    UI* m_ui;
    std::vector<int> m_data;
    std::vector<int> m_originalData; // Store the original unsorted data
    std::string m_algorithmName;
    int m_comparisons;
    int m_moves;
    int m_highlightIndex1;
    int m_highlightIndex2;
    int m_sortedUpToIndex;  // Index up to which elements are sorted
    
    // Calculate the width of each bar based on window size and data size
    float calculateBarWidth() const;
    
    // Calculate the height of each bar based on window size and data value
    float calculateBarHeight(int value) const;
};

#endif // VISUALIZATION_H 