#ifndef COMMANDS_H
#define COMMANDS_H

#include "var.h"

void toggle_stretch_n_scale() {

}

void toggle_inverse_color() {

}

void zoom_image() {
    zoom.x -= am_zoom;
    zoom.y -= am_zoom;
    zoom.w += am_zoom;
    zoom.h += am_zoom;
}

void zoom_out() {
    zoom.x += am_zoom;
    zoom.y += am_zoom;
    zoom.w -= am_zoom;
    zoom.h -= am_zoom;
}

void toggle_fit() {

}

void toggle_fill() {

}

#endif
