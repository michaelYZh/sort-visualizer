#include "data.h"
#include "apstring.h"

///constructor
Data::Data() {
    memoryUsage = 0;
    comparison = 0;
    moves = 0;
}

///overloading constructor with a given length of integers
Data::Data(int dataSize) {
    srand(time(NULL));
    memoryUsage = 0;
    comparison = 0;
    moves = 0;
    data.resize(dataSize);

    //use a for loop to set the initial value of list all to -1
    for(int i = 0; i < dataSize; i++) {
        data[i] = -1;
    }

    //use a for loop to randomly distribute the integers
    for(int i = 1; i <= dataSize; i++) {
        int index = rand() % dataSize; //select a random location for the integer

        //check if the location is already occupied by an integer
        if(data[index] == -1)
            data[index] = i; //if not then place integer on the selected location
        else {
            i--;        //if yes then go back one iteration
            continue;   //and repeat the process of selecting a random location
        }
    }

    backup = data; //get of copy of the list
}

///constructor
Data::~Data() {}

///sorting the list in ascending order by using recursive merge sort
void Data::mergeSort(int startIndex, int endIndex) {

    //ends when there are only two numbers left to sort
    if(startIndex < endIndex) {
        int middle = (startIndex + endIndex) / 2;
        mergeSort(startIndex, middle); //sort the first half
        mergeSort(middle + 1, endIndex); //sort the second half
        mergeList(startIndex, middle, endIndex); //merge the sorted the parts together
    }
}

///private method that merge two lists together in an ascending order
void Data::mergeList(int startIndex, int middle, int endIndex) {

    int firstCounter = 0, secondCounter = 0, dataIndex = startIndex;
    apvector<int> firstHalf(middle - startIndex + 1);
    apvector<int> secondHalf(endIndex - middle);

    //copy the first half the list to an apvector
    for(int i = 0; i < firstHalf.length(); i++) {
        firstHalf[i] = data[startIndex + i];
    }

    //copy the first half the list to another apvector
    for(int i = 0; i < secondHalf.length(); i++) {
        secondHalf[i] = data[middle + 1 + i];
    }

    //calculate the memory usage of merge sort
    memoryUsage = 0;
    memoryUsage += sizeof(firstHalf[0]) * firstHalf.length();
    memoryUsage += sizeof(secondHalf[0]) * secondHalf.length();
    memoryUsage += sizeof(data[0]) * data.length();

    //use a while loop to merge the two parts together
    while(firstCounter < firstHalf.length() && secondCounter < secondHalf.length()) {
        comparison++;
        visual(0, SCREENHEIGHT, dataIndex); //call method to display the visual of the current list

        //check to put the smaller integer in the list first
        if(firstHalf[firstCounter] <= secondHalf[secondCounter]) {
            data[dataIndex] = firstHalf[firstCounter];
            firstCounter++; //get ready to compare the next item
        } else {
            data[dataIndex] = secondHalf[secondCounter];
            secondCounter++; //get ready to compare the next item
        }

        moves++;
        visual(0, SCREENHEIGHT, dataIndex);  //call method to display the visual of the current list
        dataIndex++;
    }

    //check if there are any left over integers in the first half list
    if(firstCounter == firstHalf.length()) {

        //put the rest of the integers into the final list
        for(int i = secondCounter; i < secondHalf.length(); i++) {
            comparison++;
            visual(0, SCREENHEIGHT, dataIndex); //call method to display the visual of the current list
            data[dataIndex] = secondHalf[i];
            moves++;
            visual(0, SCREENHEIGHT, dataIndex); //call method to display the visual of the current list
            dataIndex++;
        }
    }

    //check if there are any left over integers in the second half list
    if(secondCounter == secondHalf.length()) {

        //put the rest of the integers into the final list
        for(int i = firstCounter; i < firstHalf.length(); i++) {
            comparison++;
            visual(0, SCREENHEIGHT, dataIndex); //call method to display the visual of the current list
            data[dataIndex] = firstHalf[i];
            moves++;
            visual(0, SCREENHEIGHT, dataIndex); //call method to display the visual of the current list
            dataIndex++;
        }
    }
}

///sorting the list in ascending order by using recursive quick sort
void Data::quickSort(int startIndex, int endIndex) {

    //ends when there are only two numbers left to sort
    if(startIndex < endIndex) {
        //call method split the list into two parts according to the pivot
        int pivotPosiiton = pivotPartition(startIndex, endIndex);
        quickSort(startIndex, pivotPosiiton - 1); //repeat for the part before the pivot
        quickSort(pivotPosiiton + 1, endIndex); //repeat for the part after the pivot
    }
}

///private method to sort split the list into two parts and return the index of pivot
int Data::pivotPartition(int startIndex, int endIndex) {
    int pivot = data[endIndex];
    int counter = startIndex;

    //loop through the items before the pivot
    for(int i = startIndex; i < endIndex; i++) {
        visual(0, SCREENHEIGHT, i); //call method to display the visual of the current list
        comparison++;

        //when meet a item that should be in front of the pivot
        if(data[i] < pivot) {
            moves++;
            int temp = data[counter];
            data[counter] = data[i];
            data[i] = temp;
            counter++;
            visual(0, SCREENHEIGHT, i); //call method to display the visual of the current list
        }
    }

    //put the pivot in correct position
    int temp = data[counter];
    data[counter] = pivot;
    data[endIndex] = temp;
    moves++;
    visual(0, SCREENHEIGHT, endIndex); //call method to display the visual of the current list

    return counter;
}

///sorting the list in ascending order by using insertion sort
void Data::insertionSort() {

    //loop through the list
    for(int i = 1; i < data.length(); i++) {
        int j = i - 1;
        int temp = data[i];

        //use a while to find the correct position for the currently sorting item
        while(j >= 0 && data[j] > temp) {
            comparison++;
            data[j+1] = data[j]; //shift every item to the right
            visual(0, SCREENHEIGHT, j); //call method to display the visual of the current list
            j--;
        }

        data[j+1] = temp; //insert the item to its position
        moves++;
        visual(0, SCREENHEIGHT, i); //call method to display the visual of the current list
    }
}

///sorting the list in ascending order by using selection sort
void Data::selectionSort() {

    //loop through the list
    for(int i = 0; i < data.length() - 1; i++) {
        int minimum = i;

        //use a for loop the go through the unsorted portion and find the smallest item in the portion
        for (int j = i + 1; j < data.length(); j++) {
            visual(0, SCREENHEIGHT, j); //call method to display the visual of the current list
            comparison++;
            if(data[j] < data[minimum])
                minimum = j;
        }

        int temp = data[i]; //place the smallest item in the correct position
        data[i] = data[minimum];
        data[minimum] = temp;
        moves++;
        visual(0, SCREENHEIGHT, i); //call method to display the visual of the current list
    }
}

///private method for the graphical part of the list
void Data::visual(float x1, float y1, int index) {

    al_clear_to_color(BACKGROUNDCOLOUR); //set background to black

    float xspacing = SCREENLENGTH / LENGTH * 1.0; //calculate the space between each column
    float yratio = (double) NUMBERRANGE / LENGTH; //calculate the relative height for display


    //loop through the list and draw the item's corresponding height
    for(int i = 0; i < data.length(); i++) {
        al_draw_line(x1 + xspacing * i, y1, x1 + xspacing * i, y1 - data[i] * yratio, FONTCOLOUR, xspacing);
    }

    //draw a red line to indicate the current sorting progress
    al_draw_line(x1 + xspacing * index, y1, x1 + xspacing * index, y1 - data[index] * yratio, INDICATION, INDICATIONTHICKNESS * xspacing);

    drawComparison();  //call private method that draws the number of comparison
    drawTimer();       //call private method that draws the time
    drawMoves();       //call private method that draws the number of movements
    drawMemoryUsage(); //call private method that draws the memory usage
    drawBackButton();  //call private method that draws the return button

    al_flip_display(); //display
}

///resets all comparative variables to zero and restore the initial arrangement of the list
void Data::reset() {
    memoryUsage = 0;
    comparison = 0;
    moves = 0;

    //use a for loop to set data to the initial value
    for(int i = 0; i < data.length(); i++) {
        data[i] = backup[i];
    }
}

///method to start the timer
void Data::startTime() {
    memoryUsage = sizeof(data[0]) * data.length();
    time_req = clock();
}

///method to end the timer
void Data::endTime() {
    time_req = clock()- time_req;
    secondPassed = (double)time_req / CLOCKS_PER_SEC; //calculate how many second have passed
}

///private method to draw the number of movements
void Data::drawMoves() {
    apstring movements = "Moves: ";
    movements += to_string(getMoves()).c_str();
    al_draw_text(stasFont, FONTCOLOUR, MOVESX, 0, NULL, movements.c_str());
}

///private method to draw the number of comparisons
void Data::drawComparison() {
    apstring compare = "Comparison: ";
    compare += to_string(getComparison()).c_str();
    al_draw_text(stasFont, FONTCOLOUR, COMPARISONX, 0, NULL, compare.c_str());
}

///private method to draw the time
void Data::drawTimer() {
    endTime();
    apstring timer = "Timer: ";
    timer += to_string(getTime()).c_str();
    al_draw_text(stasFont, FONTCOLOUR, TIMERX, 0, NULL, timer.c_str());
}

///private method to draw the memory usage
void Data::drawMemoryUsage() {
    endTime();
    apstring memory = "Memory Usage: ";
    memory += to_string(getMemoryUsage()).c_str();
    memory += " bytes";
    al_draw_text(stasFont, FONTCOLOUR, MEMORYX, 0, NULL, memory.c_str());
}

///private method to draw the return button
void Data::drawBackButton() {
    al_draw_filled_triangle(BACKX1, BACKY1, BACKX1, BACKY2, BACKX2, (BACKY2 + BACKY1) / 2., TITLECOLOUR);
}

void Data::restart(){
    memoryUsage = 0;
    comparison = 0;
    moves = 0;
    int number = data.length();
    srand(time(NULL));

    //use a for loop to set the initial value of list all to -1
    for(int i = 0; i < number; i++) {
        data[i] = -1;
    }

    //use a for loop to randomly distribute the integers
    for(int i = 1; i <= number; i++) {
        int index = rand() % number; //select a random location for the integer

        //check if the location is already occupied by an integer
        if(data[index] == -1)
            data[index] = i; //if not then place integer on the selected location
        else {
            i--;        //if yes then go back one iteration
            continue;   //and repeat the process of selecting a random location
        }
    }

    backup = data; //get of copy of the list
}
