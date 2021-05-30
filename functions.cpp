#include "graphicalSorting.h"

//function that draws the title out
void titleDisplay() {

    //draw title
    al_draw_text(titleFont, TITLECOLOUR, SCREENLENGTH / 2., SCREENHEIGHT / 2., ALLEGRO_ALIGN_CENTER, "GRAPHICAL SORTING");
    al_flip_display(); //display

}

//function that destroys all allegro variables to prevent memory leak
void destroyAllegro() {

    al_destroy_display(display);
    al_destroy_font(titleFont);
    al_destroy_font(stasFont);
    al_destroy_font(arial);
    al_destroy_font(buttonFont);
    al_destroy_event_queue(event_queue);

}

//function that draws the user interface page
void userInterface() {

    al_clear_to_color(BACKGROUNDCOLOUR); //set background to black

    //draw instructions
    al_draw_text(arial, FONTCOLOUR, SCREENLENGTH / 2., INSTRUCTIONY, ALLEGRO_ALIGN_CENTER,
                 "THIS PROGRAM COMPARES DEFFIRENT SORT ALGORITHIMS");

    al_draw_text(arial, FONTCOLOUR, SCREENLENGTH / 2., INSTRUCTIONY + 50, ALLEGRO_ALIGN_CENTER,
                 "CLICK TO SEE ONE OF THEM");

    //use a for loop to draw the four buttons for different sorting algorithm
    for(int i = 0; i < 2; i++) {
        float x1 = BUTTONX1 + i * (BUTTONX1 + BUTTONLENGTH);
        float x2 = BUTTONX1 + BUTTONLENGTH + i * (BUTTONX1 + BUTTONLENGTH);
        al_draw_filled_rounded_rectangle(x1, BUTTONY1, x2, BUTTONY1 + BUTTONHEIGHT, BUTTONROUND, BUTTONROUND, TITLECOLOUR);
        al_draw_filled_rounded_rectangle(x1, BUTTONY2, x2, BUTTONY2 + BUTTONHEIGHT, BUTTONROUND, BUTTONROUND, TITLECOLOUR);
    }

    //calculate the coordinates for the text on the buttons
    float textX1 = BUTTONX1 + 0.5 * BUTTONLENGTH;
    float textY1 = BUTTONY1 + 0.5 * BUTTONHEIGHT - 0.5 * BUTTONFONTSIZE;
    float textX2 = 2.0 * BUTTONX1 + 1.5 * BUTTONLENGTH;
    float textY2 = BUTTONY2 + 0.5 * BUTTONHEIGHT - 0.5 * BUTTONFONTSIZE;

    //draw the names on the button
    al_draw_text(buttonFont, FONTCOLOUR, textX1, textY1, ALLEGRO_ALIGN_CENTER, "QUICK SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX2, textY1, ALLEGRO_ALIGN_CENTER, "MERGE SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX1, textY2, ALLEGRO_ALIGN_CENTER, "INSERTION SORT");
    al_draw_text(buttonFont, FONTCOLOUR, textX2, textY2, ALLEGRO_ALIGN_CENTER, "SELECTION SORT");

    //draw the restart button
    al_draw_filled_rounded_rectangle(SCREENLENGTH / 2. - RESTARTHALFLENGTH, RESTARTY,
                                     SCREENLENGTH / 2. + RESTARTHALFLENGTH, RESTARTY + RESRARTHEIGHT,
                                     RESTARTROUND, RESTARTROUND, TITLECOLOUR);

    //draw text on the restart button
    al_draw_text(buttonFont, FONTCOLOUR, SCREENLENGTH / 2., RESTARTY + 0.5 * RESRARTHEIGHT - 0.5 * BUTTONFONTSIZE,
                 ALLEGRO_ALIGN_CENTER, "RESTART");

    al_flip_display(); //display
}
