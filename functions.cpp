#include "graphicalSorting.h"

// see graphicalSorting.h for details
void titleDisplay() {
    al_draw_text(titleFont, TITLECOLOUR, SCREENLENGTH / 2., SCREENHEIGHT / 2., 
                 ALLEGRO_ALIGN_CENTER, "GRAPHICAL SORTING");
    al_flip_display();
}

// see graphicalSorting.h for details
void destroyAllegro() {
    al_destroy_display(display);
    al_destroy_font(titleFont);
    al_destroy_font(stasFont);
    al_destroy_font(arial);
    al_destroy_font(buttonFont);
    al_destroy_event_queue(event_queue);
}

// see graphicalSorting.h for details
void userInterface() {
    al_clear_to_color(BACKGROUNDCOLOUR);

    al_draw_text(arial, FONTCOLOUR, SCREENLENGTH / 2., 
                 INSTRUCTIONY, ALLEGRO_ALIGN_CENTER,
                 "THIS PROGRAM COMPARES DEFFIRENT SORT ALGORITHIMS");
    al_draw_text(arial, FONTCOLOUR, SCREENLENGTH / 2., INSTRUCTIONY + 50, 
                 ALLEGRO_ALIGN_CENTER,
                 "CLICK TO SEE ONE OF THEM");

    for(int i = 0; i < 2; i++) {
        float x1 = BUTTONX1 + i * (BUTTONX1 + BUTTONLENGTH);
        float x2 = BUTTONX1 + BUTTONLENGTH + i * (BUTTONX1 + BUTTONLENGTH);
        al_draw_filled_rounded_rectangle(x1, BUTTONY1, x2, 
            BUTTONY1 + BUTTONHEIGHT, BUTTONROUND, BUTTONROUND, TITLECOLOUR);
        al_draw_filled_rounded_rectangle(x1, BUTTONY2, x2, 
            BUTTONY2 + BUTTONHEIGHT, BUTTONROUND, BUTTONROUND, TITLECOLOUR);
    }

    //calculate the coordinates for the text on the buttons
    float textX1 = BUTTONX1 + 0.5 * BUTTONLENGTH;
    float textY1 = BUTTONY1 + 0.5 * BUTTONHEIGHT - 0.5 * BUTTONFONTSIZE;
    float textX2 = 2.0 * BUTTONX1 + 1.5 * BUTTONLENGTH;
    float textY2 = BUTTONY2 + 0.5 * BUTTONHEIGHT - 0.5 * BUTTONFONTSIZE;

    al_draw_text(buttonFont, FONTCOLOUR, textX1, textY1, 
                 ALLEGRO_ALIGN_CENTER, "QUICK SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX2, textY1, 
                 ALLEGRO_ALIGN_CENTER, "MERGE SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX1, textY2, 
                 ALLEGRO_ALIGN_CENTER, "INSERTION SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX2, textY2, 
                 ALLEGRO_ALIGN_CENTER, "SELECTION SORT");

    al_draw_filled_rounded_rectangle(SCREENLENGTH / 2. - RESTARTHALFLENGTH, 
        RESTARTY, SCREENLENGTH / 2. + RESTARTHALFLENGTH, 
        RESTARTY + RESRARTHEIGHT, RESTARTROUND, RESTARTROUND, TITLECOLOUR);

    al_draw_text(buttonFont, FONTCOLOUR, SCREENLENGTH / 2., 
                 RESTARTY + 0.5 * RESRARTHEIGHT - 0.5 * BUTTONFONTSIZE,
                 ALLEGRO_ALIGN_CENTER, "RESTART");

    al_flip_display();
}
