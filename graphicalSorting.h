#ifndef _graphicalSorting_h_
#define _graphicalSorting_h_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include <ctime>
#include <cstdio>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

//user define variables
#define LENGTH 1000
#define NUMBERRANGE 500
#define SCREENLENGTH 1000
#define SCREENHEIGHT 650
#define TITLECOLOUR al_map_rgb(0, 0, 255)
#define FONTCOLOUR al_map_rgb(255, 255, 255)
#define INDICATION al_map_rgb(255, 0, 0)
#define INDICATIONTHICKNESS 2
#define BACKGROUNDCOLOUR al_map_rgb(0, 0, 0)
#define BUTTONLENGTH 350
#define BUTTONHEIGHT 170
#define BUTTONROUND 30
#define BUTTONX1 100
#define BUTTONY1 160
#define BUTTONY2 385
#define INSTRUCTIONY 50
#define BUTTONFONTSIZE 35
#define TIMERX 0
#define COMPARISONX 250
#define MOVESX 500
#define MEMORYX 700
#define BACKX1 100
#define BACKX2 30
#define BACKY1 40
#define BACKY2 120
#define RESTARTHALFLENGTH 100
#define RESTARTY 580
#define RESRARTHEIGHT 50
#define RESTARTROUND 10

enum STATUS {SORT, BACK};

//allegro variable declaration
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *titleFont;
extern ALLEGRO_FONT *stasFont;
extern ALLEGRO_FONT *arial;        //arial font
extern ALLEGRO_FONT *buttonFont;
extern ALLEGRO_EVENT_QUEUE *event_queue;


// initializeAllegro() intializes the window and font for allegro                                                                          
int initializeAllegro();
// void titleDisplay() displays the title on the window
void titleDisplay();
// destroyAllegro() destroys all allegro variables
void destroyAllegro();
// userInterface() draws the user interface on the window
void userInterface();
// quicksortHB(mouse_state) determines if the mouse position
//   is within the button for quicksort.
bool quicksortHB(ALLEGRO_MOUSE_STATE mouse_state);
// mergesortHB(mouse_state) determines if the mouse position
//   is within the button for merge sort.
bool mergesortHB(ALLEGRO_MOUSE_STATE mouse_state);
// insertionsortHB(mouse_state) determines if the mouse position
//   is within the button for insertion sort.
bool insertionsortHB(ALLEGRO_MOUSE_STATE mouse_state);
// selectionsortHB(mouse_state) determines if the mouse position
//   is within the button for selection sort.
bool selectionHB(ALLEGRO_MOUSE_STATE mouse_state);
// backHB(mouse_state) determines if the mouse position is within 
//   the button for back
bool backHB(ALLEGRO_MOUSE_STATE mouse_state);
// restartHB(mouse_state) determines if the mouse position is within 
//   the button for restart
bool restartHB(ALLEGRO_MOUSE_STATE mouse_state);

#endif // _graphicalSorting_h_
