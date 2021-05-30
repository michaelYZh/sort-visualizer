/*************************************************************************************************************
Project: Graphical Sorting Assignment
Description: This program compares four sorting algorithms namely; quick sort, merge sort, insertion sort
             and selection sort through graphical representation.
History: Michael Zhang June 7th, 2019
Functions:
int initializeAllegro();    -return int     -function that initializes allegro
void titleInstructionDisplay();     -no return      -function that displays the title
void destroyAllegro();      -no return      -function that destroys all allegro variables
void userInterface();       -no return      -function that draws the user interface
bool quicksortHB(ALLEGRO_MOUSE_STATE mouse_state);
-return boolean     -function that checks if the user
        clicks the quick sort button
bool mergesortHB(ALLEGRO_MOUSE_STATE mouse_state);  -return boolean     -function that checks if the user
                                                                         clicks the merge sort button
bool insertionsortHB(ALLEGRO_MOUSE_STATE mouse_state);  -return boolean     -function that checks if the user
                                                                             clicks the insertion sort button
bool selectionHB(ALLEGRO_MOUSE_STATE mouse_state);  -return boolean     -function that checks if the user
                                                                         clicks the selection sort button
bool backHB(ALLEGRO_MOUSE_STATE mouse_state);       -return boolean     -function that checks if the user
                                                                         clicks the return button
bool restartHB(ALLEGRO_MOUSE_STATE mouse_state);    -return boolean     -function that checks if the user
                                                                         clicks the restart button
************************************************************************************************************/

#include "graphicalSorting.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *titleFont;
ALLEGRO_FONT *stasFont;
ALLEGRO_FONT *arial;        //arial font
ALLEGRO_FONT *buttonFont;
ALLEGRO_EVENT_QUEUE *event_queue;

int main() {
    //call function to set up allegro
    initializeAllegro();

    Data dataList(LENGTH);
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_EVENT event;
    bool drawInterface = true;
    STATUS task = SORT;

    //call function to display the title
    titleDisplay();

    //use a while loop to make the user stay at the title page
    while(true) {

        al_wait_for_event(event_queue, &event); //wait for the user to click

        //check if the user click or not
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            break;
        }

        //check if the user click the close button
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            destroyAllegro(); //call function to destroy all allegro variables
            return 0;         //exit the program
        }
    }

    //use a while loop to let the user keep seeing different sorting
    while(true) {

        al_get_mouse_state(&mouse_state); //get the mouse movement
        al_wait_for_event(event_queue, &event); //wait for the user to click

        if(drawInterface) {
            userInterface(); //call function to draw the menu page
        }


        //check if the user click the close button
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        //check if the user press the key
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            //check if the user clicks on the restart button
            if(restartHB(mouse_state)) {
                dataList.restart(); //call method the reassign random numbers to the list
                continue;           //start a new iteration
            }

            //check if the user clicks on the quick sort button
            if(quicksortHB(mouse_state) && task == SORT) {
                dataList.startTime(); //call method to start the timer
                dataList.quickSort(0, LENGTH - 1); //call method to quick sort the list
                task = BACK;
            }

            //check if the user clicks on the merge sort button
            else if(mergesortHB(mouse_state) && task == SORT) {
                dataList.startTime(); //call method to start the timer
                dataList.mergeSort(0, LENGTH - 1); //call method to merge sort the list
                task = BACK;
            }

            //check if the user clicks on the insertion sort button
            else if(insertionsortHB(mouse_state) && task == SORT) {
                dataList.startTime(); //call method to start the timer
                dataList.insertionSort(); //call method to insertion sort the list
                task = BACK;
            }

            //check if the user clicks on the selection sort button
            else if(selectionHB(mouse_state) && task == SORT) {
                dataList.startTime(); //call method to start the timer
                dataList.selectionSort(); //call method to selection sort the list
                task = BACK;
            }

            drawInterface = false; //make the user stay at the sorting page

            //check if the user clicks on the return button
            if(backHB(mouse_state) && task == BACK) {
                dataList.reset(); //call method to reset all comparative values
                drawInterface = true;
                task = SORT;
            }
        }
    }

    //call function to destroy all allegro variables
    destroyAllegro();
    return 0;
}
