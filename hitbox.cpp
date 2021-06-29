#include "graphicalSorting.h"

// see graphicalSorting.h for details
bool quicksortHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x2 = BUTTONX1 + BUTTONLENGTH;
    float y2 = BUTTONY1 + BUTTONHEIGHT;

    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= BUTTONX1 && x <= x2 && y >= BUTTONY1 && y <= y2)
        return true;

    return false;
}

// see graphicalSorting.h for details
bool mergesortHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x1 = BUTTONX1 + BUTTONX1 + BUTTONLENGTH;
    float x2 = x1 + BUTTONLENGTH;
    float y2 = BUTTONY1 + BUTTONHEIGHT;

    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= x1 && x <= x2 && y >= BUTTONY1 && y <= y2)
        return true;

    return false;
}

// see graphicalSorting.h for details
bool insertionsortHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x2 = BUTTONX1 + BUTTONLENGTH;
    float y2 = BUTTONY2 + BUTTONHEIGHT;

    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= BUTTONX1 && x <= x2 && y >= BUTTONY2 && y <= y2)
        return true;

    return false;
}

// see graphicalSorting.h for details
bool selectionHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x1 = BUTTONX1 + BUTTONX1 + BUTTONLENGTH;
    float x2 = x1 + BUTTONLENGTH;
    float y2 = BUTTONY2 + BUTTONHEIGHT;

    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= x1 && x <= x2 && y >= BUTTONY2 && y <= y2)
        return true;

    return false;
}

// see graphicalSorting.h for details
bool backHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= BACKX2 && x <= BACKX1 && y >= BACKY1 && y <= BACKY2)
        return true;

    return false;
}

// see graphicalSorting.h for details
bool restartHB(ALLEGRO_MOUSE_STATE mouse_state) {
    float x1 = SCREENLENGTH / 2. - RESTARTHALFLENGTH;
    float x2 = SCREENLENGTH / 2. + RESTARTHALFLENGTH;
    float y2 = RESTARTY + RESRARTHEIGHT;

    float x = mouse_state.x;
    float y = mouse_state.y;

    if(x >= x1 && x <= x2 && y >= RESTARTY && y <= y2)
        return true;

    return false;
}
