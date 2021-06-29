#include "graphicalSorting.h"

int initializeAllegro() {
    // Initialize Allegro
    al_init();

    // initialize display
    display = al_create_display(SCREENLENGTH, SCREENHEIGHT);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(display, "Graphical Sorting");

    // need to add image processor
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Add fonts
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    titleFont = al_load_ttf_font("Assets/LVDCGO__.ttf", 40, 0);
    if (!titleFont) {
        al_show_native_message_box(display, "Error", "Error", "Could not load LVDCGO__.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    stasFont = al_load_ttf_font("Assets/arial.ttf", 22, 0);
    if (!stasFont) {
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    arial = al_load_ttf_font("Assets/arial.ttf", 27, 0);
    if (!arial) {
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    buttonFont = al_load_ttf_font("Assets/arial.ttf", BUTTONFONTSIZE, 0);
    if (!buttonFont) {
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
    if (!al_init_primitives_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // set up event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    al_install_mouse();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    return 0;
}
