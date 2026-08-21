#ifndef EVENTS_H
#define EVENTS_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "../../vendor/stb_image.h"

#include <stdio.h>
#include <err.h>

#include "var.h"

#include "inverse.h"
#include "center.h"
#include "redraw.h"

static int RenderEvents(XEvent event) {
    switch (event.type) {
        case Expose:
            if (event.xexpose.count == 0) {
                redraw();
            }
        break;
        
        case ConfigureNotify:
            if (win_Width != event.xconfigure.width || win_Height != event.xconfigure.height) 
            {
                win_Width  = event.xconfigure.width;
                win_Height = event.xconfigure.height;
                XFreePixmap(display, double_buffer);
                
                double_buffer = XCreatePixmap(
                        display, 
                        window, 
                        win_Width, 
                        win_Height,
                        DefaultDepth(display, DefaultScreen(display))
                );
            } 
        break;

        case KeyPress:
            key = XLookupKeysym(&event.xkey, 0);

            if (key == XK_Up)    image_y -= speed;
            if (key == XK_Down)  image_y += speed;
            if (key == XK_Left)  image_x -= speed;
            if (key == XK_Right) image_x += speed;

            if (key == XK_c) {
                center();
            }

            if (key == XK_Return) {
                inverse();
            }
        break;

        case ClientMessage: 
            if ((Atom) event.xclient.data.l[0] == wm_delete_window) {
                printf("WM_SAVE_YOUSELF\n"); // This is apart of the official ICCCM documentation. Thank you Tsoding
                return 0;
            } 
        break;
    }

    redraw(); 
    return 1;
}

static void MageQuit() {
	stbi_image_free(m_LocalBuffer);
    XFreePixmap(display, double_buffer);
	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

#endif
