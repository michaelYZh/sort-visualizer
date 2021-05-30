/******************************************************************************
Class: data
Description: This class holds a list of number and have the attributes to sort
             the list in different algorithms namely; quick sort, merge sort,
             insertion sort and selection sort
History: Michael Zhang June 7th 2019
*******************************************************************************/

#ifndef _data_h_
#define _data_h_

#include "apvector.h"
#include "graphicalSorting.h"

//Data class definition
class Data{

    public:
        Data();             //constructor
        Data(int dataSize); //overloading constructor
        ~Data();            //destructor
        void mergeSort(int startIndex, int endIndex);   //sort the list by merge sort
        void quickSort(int startIndex, int endIndex);   //sort the list by quick sort
        void insertionSort();                           //sort the list by insertion sort
        void selectionSort();                           //sort the list by selection sort
        void reset();                                   //reset all comparative variables
        int getComparison() {return comparison;};       ///returns the number of comparisons
        int getMoves() {return moves;};                 ///returns the number of movements
        int getMemoryUsage() {return memoryUsage;};     ///returns the memory usage
        double getTime() {return secondPassed;};        ///returns the time the sorting algorithm uses
        void startTime();                               //start the timer
        void endTime();                                 //end the timer
        void restart();                                 //reset the list with new random numbers

    private:
        apvector<int> data;
        apvector<int> backup;
        int memoryUsage;
        int comparison;
        int moves;
        clock_t time_req;
        double secondPassed;
        void mergeList(int startIndex, int middle, int endIndex);   //private method that merges the list by ascending order
        int pivotPartition(int startIndex, int endIndex);           //private method that sorts the two sides of the pivot
                                                                    //and returns the position of the pivot
        void visual(float x1, float y1, int index);                 //private method that displays the graphical sorting process
        void drawComparison();      //private method that draws the number of comparison
        void drawTimer();           //private method that draws the time
        void drawMemoryUsage();     //private method that draws the memory usage
        void drawMoves();           //private method that draws the number of movements
    void drawBackButton();      //private method that draws the return button
};

#endif // _data_h_
