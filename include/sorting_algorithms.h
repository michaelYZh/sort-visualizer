#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <functional>
#include <chrono>
#include "visualization.h"

class SortingAlgorithms {
public:
    SortingAlgorithms(Visualization& visualization);
    ~SortingAlgorithms() = default;
    
    // Quick Sort
    void quickSort();
    
    // Merge Sort
    void mergeSort();
    
    // Insertion Sort
    void insertionSort();
    
    // Selection Sort
    void selectionSort();
    
private:
    Visualization& m_visualization;
    
    /**
     * @brief Update the visualization during sorting
     * @param data The current state of the data
     * @param comparisons The number of comparisons
     * @param moves The number of moves
     * @param executionTime The execution time in milliseconds
     */
    void updateVisualization(const std::vector<int>& data, int comparisons, int moves, float executionTime = 0.0f);
    
    // Quick Sort helpers
    void quickSortImpl(std::vector<int>& data, int low, int high, int& comparisons, int& moves, 
                      const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime);
    int partition(std::vector<int>& data, int low, int high, int& comparisons, int& moves,
                 const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime);
    
    // Merge Sort helpers
    void mergeSortImpl(std::vector<int>& data, int left, int right, int& comparisons, int& moves,
                      const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime);
    void merge(std::vector<int>& data, int left, int mid, int right, int& comparisons, int& moves,
              const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime);
    
    // Utility functions
    void swap(std::vector<int>& data, int i, int j, int& moves);
};

#endif // SORTING_ALGORITHMS_H 