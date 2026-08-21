#ifndef CENTER_H
#define CENTER_H

#include <X11/Xlib.h>

#include "var.h"

static void center() {
	if (m_Width > win_Width) {
		image_x  = 0;
		source_x = (m_Width  - win_Width)  / 2;
	} 

	else {
		image_x = (win_Width - m_Width)  / 2;
		source_x = 0;
	}

	if (m_Height > win_Height) {
		image_y  = 0;
		source_y = (m_Height - win_Height) / 2;
	} 

	else {
		image_y = (win_Height - m_Height) / 2;
		source_y = 0;
	}
}

#endif 
