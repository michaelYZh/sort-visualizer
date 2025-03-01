/**
 * @file visualization.cpp
 * @brief Implementation of the Visualization class
 */

#include "visualization.h"
#include "ui.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

/**
 * @brief Constructor
 * @param window Reference to the SFML window
 * @param ui Pointer to the UI class
 */
Visualization::Visualization(sf::RenderWindow& window, UI* ui)
    : m_window(window)
    , m_ui(ui)
    , m_comparisons(0)
    , m_moves(0)
    , m_highlightIndex1(-1)
    , m_highlightIndex2(-1)
    , m_sortedUpToIndex(0)
{
    std::cout << "Visualization initialized." << std::endl;
}

void Visualization::initializeData(int size)
{
    m_data.resize(size);
    
    // Fill with values from 1 to size
    for (int i = 0; i < size; ++i) {
        m_data[i] = i + 1;
    }
    
    // Shuffle the data
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_data.begin(), m_data.end(), g);
    
    // Store the original unsorted data
    m_originalData = m_data;
    
    resetMetrics();
}

void Visualization::resetData()
{
    initializeData(m_data.size());
    m_sortedUpToIndex = 0;
}

void Visualization::restoreOriginalData()
{
    // Restore the original unsorted data
    m_data = m_originalData;
    resetMetrics();
    m_sortedUpToIndex = 0;
}

void Visualization::draw()
{
    const float barWidth = calculateBarWidth();
    
    for (size_t i = 0; i < m_data.size(); ++i) {
        sf::RectangleShape bar;
        bar.setSize(sf::Vector2f(barWidth - 1, calculateBarHeight(m_data[i])));
        bar.setPosition(i * barWidth, m_window.getSize().y - bar.getSize().y);
        
        // Set color based on element state
        if (static_cast<int>(i) == m_highlightIndex1 || static_cast<int>(i) == m_highlightIndex2) {
            // Highlight color for elements being compared/selected
            bar.setFillColor(sf::Color(255, 100, 100)); // Lighter red
        } else if (static_cast<int>(i) <= m_sortedUpToIndex) {
            // Color for sorted elements
            bar.setFillColor(sf::Color(100, 200, 100)); // Lighter green
        } else {
            // Default color for unsorted elements
            bar.setFillColor(sf::Color(255, 255, 255)); // Pure white
        }
        
        // Add outline to bars for better visibility
        bar.setOutlineThickness(1.0f);
        bar.setOutlineColor(sf::Color(50, 50, 50)); // Dark gray outline
        
        m_window.draw(bar);
    }
}

const std::vector<int>& Visualization::getData() const
{
    return m_data;
}

void Visualization::setData(const std::vector<int>& data)
{
    m_data = data;
}

void Visualization::updateVisualization(const std::vector<int>& data, int comparisons, int moves, float executionTime)
{
    m_data = data;
    m_comparisons = comparisons;
    m_moves = moves;
    
    // Update UI metrics
    m_ui->updateMetrics(m_comparisons, m_moves, executionTime);
    
    // Redraw the window
    m_window.clear(sf::Color(30, 30, 30));
    draw();
    m_ui->draw();
    m_window.display();
    
    // Check for exit events
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            exit(0); // Force exit the application
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            // Cancel sorting and return to menu
            return;
        }
        
        // Let UI handle other events
        m_ui->handleEvent(event);
    }
    
    // Small delay to visualize the sorting process
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Visualization::highlightElements(int index1, int index2)
{
    m_highlightIndex1 = index1;
    m_highlightIndex2 = index2;
}

void Visualization::setSortedUpToIndex(int index)
{
    m_sortedUpToIndex = index;
}

void Visualization::setAlgorithmName(const std::string& name)
{
    m_algorithmName = name;
}

sf::Vector2u Visualization::getWindowSize() const
{
    return m_window.getSize();
}

int Visualization::getComparisons() const
{
    return m_comparisons;
}

int Visualization::getMoves() const
{
    return m_moves;
}

void Visualization::resetMetrics()
{
    m_comparisons = 0;
    m_moves = 0;
    m_highlightIndex1 = -1;
    m_highlightIndex2 = -1;
    m_sortedUpToIndex = 0;
}

float Visualization::calculateBarWidth() const
{
    return static_cast<float>(m_window.getSize().x) / m_data.size();
}

float Visualization::calculateBarHeight(int value) const
{
    const float maxHeight = m_window.getSize().y * 0.7f;
    return (static_cast<float>(value) / m_data.size()) * maxHeight;
}

/**
 * @brief Set the UI reference
 * @param ui Pointer to the UI class
 */
void Visualization::setUI(UI* ui)
{
    m_ui = ui;
} 