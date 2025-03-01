#include "sorting_algorithms.h"
#include <algorithm>
#include <chrono>

SortingAlgorithms::SortingAlgorithms(Visualization& visualization)
    : m_visualization(visualization)
{
}

void SortingAlgorithms::quickSort()
{
    m_visualization.setAlgorithmName("Quick Sort");
    m_visualization.resetMetrics();
    
    std::vector<int> data = m_visualization.getData();
    int comparisons = 0;
    int moves = 0;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    quickSortImpl(data, 0, data.size() - 1, comparisons, moves, startTime);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Mark all elements as sorted
    m_visualization.setSortedUpToIndex(data.size() - 1);
    m_visualization.highlightElements(-1, -1); // Clear any highlights
    
    // Final update with execution time
    updateVisualization(data, comparisons, moves, static_cast<float>(duration));
}

void SortingAlgorithms::mergeSort()
{
    m_visualization.setAlgorithmName("Merge Sort");
    m_visualization.resetMetrics();
    
    std::vector<int> data = m_visualization.getData();
    int comparisons = 0;
    int moves = 0;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    mergeSortImpl(data, 0, data.size() - 1, comparisons, moves, startTime);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Mark all elements as sorted
    m_visualization.setSortedUpToIndex(data.size() - 1);
    m_visualization.highlightElements(-1, -1); // Clear any highlights
    
    // Final update with execution time
    updateVisualization(data, comparisons, moves, static_cast<float>(duration));
}

void SortingAlgorithms::insertionSort()
{
    m_visualization.setAlgorithmName("Insertion Sort");
    m_visualization.resetMetrics();
    
    std::vector<int> data = m_visualization.getData();
    int comparisons = 0;
    int moves = 0;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i < static_cast<int>(data.size()); ++i) {
        int key = data[i];
        int j = i - 1;
        
        // Highlight the current element being inserted
        m_visualization.highlightElements(i, -1);
        
        while (j >= 0 && data[j] > key) {
            comparisons++;
            data[j + 1] = data[j];
            moves++;
            j--;
            
            // Update visualization with current time
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
            
            // Highlight the elements being compared
            m_visualization.highlightElements(i, j);
        }
        
        data[j + 1] = key;
        moves++;
        
        // Mark elements up to i as sorted
        m_visualization.setSortedUpToIndex(i);
        
        // Update visualization with current time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Final update with no highlights
    m_visualization.highlightElements(-1, -1);
    m_visualization.setSortedUpToIndex(data.size() - 1);
    updateVisualization(data, comparisons, moves, static_cast<float>(duration));
}

void SortingAlgorithms::selectionSort()
{
    m_visualization.setAlgorithmName("Selection Sort");
    m_visualization.resetMetrics();
    
    std::vector<int> data = m_visualization.getData();
    int comparisons = 0;
    int moves = 0;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < data.size() - 1; ++i) {
        size_t minIndex = i;
        
        // Highlight the current minimum
        m_visualization.highlightElements(i, -1);
        
        for (size_t j = i + 1; j < data.size(); ++j) {
            comparisons++;
            
            // Highlight the elements being compared
            m_visualization.highlightElements(minIndex, j);
            
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
            
            // Update visualization with current time
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
        }
        
        if (minIndex != i) {
            swap(data, i, minIndex, moves);
        }
        
        // Mark elements up to i as sorted
        m_visualization.setSortedUpToIndex(i);
        
        // Update visualization with current time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    // Final update with no highlights
    m_visualization.highlightElements(-1, -1);
    m_visualization.setSortedUpToIndex(data.size() - 1);
    updateVisualization(data, comparisons, moves, static_cast<float>(duration));
}

void SortingAlgorithms::updateVisualization(const std::vector<int>& data, int comparisons, int moves, float executionTime)
{
    m_visualization.updateVisualization(data, comparisons, moves, executionTime);
}

void SortingAlgorithms::quickSortImpl(std::vector<int>& data, int low, int high, int& comparisons, int& moves, 
                                     const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime)
{
    if (low < high) {
        int pivotIndex = partition(data, low, high, comparisons, moves, startTime);
        
        // Mark elements up to pivotIndex as sorted if they are in their final position
        if (pivotIndex == low) {
            m_visualization.setSortedUpToIndex(pivotIndex);
        }
        
        quickSortImpl(data, low, pivotIndex - 1, comparisons, moves, startTime);
        
        // After the left part is sorted, mark the pivot as sorted
        m_visualization.setSortedUpToIndex(pivotIndex);
        
        quickSortImpl(data, pivotIndex + 1, high, comparisons, moves, startTime);
        
        // After both parts are sorted, mark up to high as sorted
        if (high == static_cast<int>(data.size()) - 1) {
            m_visualization.setSortedUpToIndex(high);
        }
    }
}

int SortingAlgorithms::partition(std::vector<int>& data, int low, int high, int& comparisons, int& moves,
                                const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime)
{
    int pivot = data[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        // Highlight the pivot and current element
        m_visualization.highlightElements(high, j);
        
        comparisons++;
        if (data[j] <= pivot) {
            i++;
            swap(data, i, j, moves);
            
            // Calculate current execution time
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            
            // Update visualization with current time
            updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
        } else {
            // Even if we don't swap, update the visualization with current time
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
        }
    }
    
    swap(data, i + 1, high, moves);
    
    // Update visualization with current time
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    
    return i + 1;
}

void SortingAlgorithms::mergeSortImpl(std::vector<int>& data, int left, int right, int& comparisons, int& moves,
                                     const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortImpl(data, left, mid, comparisons, moves, startTime);
        mergeSortImpl(data, mid + 1, right, comparisons, moves, startTime);
        
        merge(data, left, mid, right, comparisons, moves, startTime);
        
        // Mark the merged section as sorted
        if (right == static_cast<int>(data.size()) - 1) {
            m_visualization.setSortedUpToIndex(right);
        }
    }
}

void SortingAlgorithms::merge(std::vector<int>& data, int left, int mid, int right, int& comparisons, int& moves,
                             const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    
    for (int i = 0; i < n1; ++i) {
        L[i] = data[left + i];
        moves++;
    }
    
    for (int j = 0; j < n2; ++j) {
        R[j] = data[mid + 1 + j];
        moves++;
    }
    
    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < n1 && j < n2) {
        // Highlight the elements being compared
        m_visualization.highlightElements(left + i, mid + 1 + j);
        
        comparisons++;
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        
        moves++;
        k++;
        
        // Calculate current execution time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        
        // Update visualization with current time
        updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    }
    
    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
        moves++;
        
        // Calculate current execution time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        
        // Update visualization with current time
        updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    }
    
    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
        moves++;
        
        // Calculate current execution time
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        
        // Update visualization with current time
        updateVisualization(data, comparisons, moves, static_cast<float>(elapsedTime));
    }
    
    // Mark the merged section as sorted
    m_visualization.setSortedUpToIndex(right);
}

void SortingAlgorithms::swap(std::vector<int>& data, int i, int j, int& moves)
{
    if (i != j) {
        std::swap(data[i], data[j]);
        moves++;
    }
} 