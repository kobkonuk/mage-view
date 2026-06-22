#ifndef REDRAW_H
#define REDRAW_H

#include <X11/Xlib.h>
#include <stdio.h>

static void redraw(Display *display, 
        Window window, 
        XImage *image, 
        Pixmap double_buffer, 
        GC gc, 
        int source_x, int source_y, 
        int image_x, int image_y, 
        int m_Width, int m_Height, 
        int win_Width, int win_Height
) {
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
	XFillRectangle(display, double_buffer, gc, 0, 0, win_Width, win_Height);
	
    XPutImage(display, double_buffer, 
			gc, image, 
			source_x, source_y, 
			image_x, image_y, 
			m_Width, 
			m_Height);
	
    XCopyArea(display, double_buffer, window, gc,
		  0, 0, win_Width, win_Height, 0, 0);
	XFlush(display);
}

#endif
