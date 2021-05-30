#include "graphicalSorting.h"

//function that checks if the user clicks the quick sort button
bool quicksortHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinates for the button
    float x2 = BUTTONX1 + BUTTONLENGTH;
    float y2 = BUTTONY1 + BUTTONHEIGHT;

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= BUTTONX1 && x <= x2 && y >= BUTTONY1 && y <= y2)
        return true;

    return false;
}

//function that checks if the user clicks the merge sort button
bool mergesortHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinates for the button
    float x1 = BUTTONX1 + BUTTONX1 + BUTTONLENGTH;
    float x2 = x1 + BUTTONLENGTH;
    float y2 = BUTTONY1 + BUTTONHEIGHT;

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= x1 && x <= x2 && y >= BUTTONY1 && y <= y2)
        return true;

    return false;
}

//function that checks if the user clicks the insertion sort button
bool insertionsortHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinates for the button
    float x2 = BUTTONX1 + BUTTONLENGTH;
    float y2 = BUTTONY2 + BUTTONHEIGHT;

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= BUTTONX1 && x <= x2 && y >= BUTTONY2 && y <= y2)
        return true;

    return false;
}

//function that checks if the user clicks the selection sort button
bool selectionHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinates for the button
    float x1 = BUTTONX1 + BUTTONX1 + BUTTONLENGTH;
    float x2 = x1 + BUTTONLENGTH;
    float y2 = BUTTONY2 + BUTTONHEIGHT;

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= x1 && x <= x2 && y >= BUTTONY2 && y <= y2)
        return true;

    return false;
}

//function that checks if the user clicks the return button
bool backHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= BACKX2 && x <= BACKX1 && y >= BACKY1 && y <= BACKY2)
        return true;

    return false;
}

//function that checks if the user clicks the restart button
bool restartHB(ALLEGRO_MOUSE_STATE mouse_state) {

    //calculate x y coordinates for the button
    float x1 = SCREENLENGTH / 2. - RESTARTHALFLENGTH;
    float x2 = SCREENLENGTH / 2. + RESTARTHALFLENGTH;
    float y2 = RESTARTY + RESRARTHEIGHT;

    //calculate x y coordinate of the mouse
    float x = mouse_state.x;
    float y = mouse_state.y;

    //check if the mouse moves into the button
    if(x >= x1 && x <= x2 && y >= RESTARTY && y <= y2)
        return true;

    return false;
}
