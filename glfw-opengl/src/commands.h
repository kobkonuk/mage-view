#ifndef COMMANDS_H
#define COMMANDS_H

#include "var.h"
#include <stdbool.h>

int zoom_xy() {
    int temp = am - am_zoom;
    return temp;
}
int zoom_wh() {
    int temp = 2 * am_zoom - am;
    return temp;
}
int fit(int var, int ivar) {
    int temp = (var - ivar) /2;
    return temp;
}
int fill() {
    int temp;
    return temp;
}
int center() {
    int temp;
    return temp;
}

void position_check() {
    pos.x = zoom_xy() + mos.x;
    pos.y = zoom_xy() + mos.y;
    pos.w = iwidth + zoom_wh();
    pos.h = iheight + zoom_wh();
}

#endif
