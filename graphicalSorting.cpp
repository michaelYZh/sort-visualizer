/*******************************************************************************
Project: Graphical Sorting Assignment
Description: This program compares four sorting algorithms namely; quick sort, 
               merge sort, insertion sort and selection sort through graphical 
               representation.
History: Michael Zhang June 7th, 2019
*******************************************************************************/

#include "graphicalSorting.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *titleFont;
ALLEGRO_FONT *stasFont;
ALLEGRO_FONT *arial;        //arial font
ALLEGRO_FONT *buttonFont;
ALLEGRO_EVENT_QUEUE *event_queue;

int main() {
    initializeAllegro(); // set up allegro

    Data dataList(LENGTH);
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_EVENT event;
    bool drawInterface = true;
    STATUS task = SORT;

    titleDisplay();

    // stay on the title page until the user clicks
    while(true) {

        al_wait_for_event(event_queue, &event);

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            break;
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            destroyAllegro(); // destroys all allegro variables
            return 0;
        }
    }

    while(true) {

        al_get_mouse_state(&mouse_state);
        al_wait_for_event(event_queue, &event);

        if(drawInterface) {
            userInterface();
        }

        // click close button
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            if(restartHB(mouse_state)) {
                dataList.restart();
                continue;          
            }

            if(quicksortHB(mouse_state) && task == SORT) {
                dataList.startTime();
                dataList.quickSort(0, LENGTH - 1);
                task = BACK;
            }

            else if(mergesortHB(mouse_state) && task == SORT) {
                dataList.startTime();
                dataList.mergeSort(0, LENGTH - 1);
                task = BACK;
            }

            else if(insertionsortHB(mouse_state) && task == SORT) {
                dataList.startTime();
                dataList.insertionSort();
                task = BACK;
            }

            else if(selectionHB(mouse_state) && task == SORT) {
                dataList.startTime();
                dataList.selectionSort();
                task = BACK;
            }

            drawInterface = false; // make the user stay at the sorting page

            if(backHB(mouse_state) && task == BACK) {
                dataList.reset();
                drawInterface = true;
                task = SORT;
            }
        }
    }

    destroyAllegro();
    return 0;
}
