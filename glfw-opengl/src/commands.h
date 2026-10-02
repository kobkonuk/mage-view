#ifndef COMMANDS_H
#define COMMANDS_H

#include "var.h"
#include <stdbool.h>

float zoom_xy() {
    float temp = am - am_zoom;
    return temp;
}
float pos_div() {
	float temp = pos.x / pos.y;
	return temp;
}
float zoom_wh() {
    float temp = 2 * (am_zoom - am) * pos_div();
    return temp;
}
float fit(float var, float ivar) {
    float temp = (var - ivar) /2;
    return temp;
}
float fill() {
    float temp;
    return temp;
}
float center() {
    float temp;
    return temp;
}

void position_check() {
    pos.x = zoom_xy() + mos.x;
    pos.y = zoom_xy() + mos.y;
    pos.w = iwidth + zoom_wh();
    pos.h = iheight + zoom_wh();
}

#endif
