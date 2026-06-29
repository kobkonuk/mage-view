#ifndef EVENTS_H
#define EVENTS_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "../vendor/stb_image.h"

#include <stdio.h>
#include <string.h>
#include <err.h>

#include "inverse.h"
#include "center.h"
#include "redraw.h"

Display *display;
XImage *image;

Window window;
GC gc;
XWindowAttributes wa = {0};	
unsigned char *m_LocalBuffer;
Pixmap double_buffer;

Atom wm_delete_window;

int win_Width;
int win_Height;

int m_Width;
int m_Height; 
int m_BPP;

static void MageInit(char *argv[]) 
{    
    display = XOpenDisplay(NULL);
	if (display == NULL) err(1, "XOpenDisplay: error");
    
    win_Width = m_Width;
	win_Height = m_Height; //Make sure image is rendered differently depending on the window size
	
	m_LocalBuffer = stbi_load(
			argv[1], 
			&m_Width, 
			&m_Height, 
			&m_BPP, 4
    );

    window = XCreateSimpleWindow(
			display,
			XDefaultRootWindow(display),
			0, 0,
			m_Width, m_Height,
			0,
			0x00000000,
			0x00000000
    );
	
	inverse(m_LocalBuffer, m_Width, m_Height); 
	XGetWindowAttributes(display, window, &wa);


    gc = XCreateGC(display, window, 0, NULL);	

	wm_delete_window = XInternAtom(
			display, 
			"WM_DELETE_WINDOW", 
			False
    );

    double_buffer =  XCreatePixmap(
            display, 
            window, 
            m_Width, 
            m_Height, 
            DefaultDepth(display, DefaultScreen(display))
    );
	
	XSetWMProtocols(
            display, 
            window, 
            &wm_delete_window, 
            1
    );

	XSelectInput(display, window, 
			KeyPressMask | 
			ExposureMask |
			StructureNotifyMask
    );

	XMapWindow(display, window);
}

int image_x  = 0;
int image_y  = 0;
int source_x = 0;
int source_y = 0;

static int RenderEvents(XEvent event) {
    XNextEvent(display, &event);
    switch (event.type) {
        case Expose:
            if (event.xexpose.count == 0) {
                redraw(display, window, image, 
                        double_buffer, gc, 
                        source_x, source_y, 
                        image_x, image_y, 
                        m_Width, m_Height, 
                        win_Width, win_Height
                );
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

        KeySym key;
        case KeyPress:
            key = XLookupKeysym(&event.xkey, 0);

            int speed = 25;

            if (key == XK_Up)    image_y -= speed;
            if (key == XK_Down)  image_y += speed;
            if (key == XK_Left)  image_x -= speed;
            if (key == XK_Right) image_x += speed;

            if (key == XK_c) {
                center(win_Width, win_Height, 
                        m_Width, m_Height, 
                        &source_x, &source_y, 
                        &image_x, &image_y
                );
            }

            if (key == XK_Return) {
                inverse(m_LocalBuffer, m_Width, m_Height);
            }
        break;

        case ClientMessage:
            if ((Atom) event.xclient.data.l[0] == wm_delete_window) {
                printf("WM_SAVE_YOUSELF\n"); // This is apart of the official ICCCM documentation. Thank you Tsoding
                return 0;
            } 
        break;

        return 1;
    }

    redraw(display, window, image, 
            double_buffer, gc, 
            source_x, source_y, 
            image_x, image_y, 
            m_Width, m_Height, 
            win_Width, win_Height
    ); 
}

static void MageQuit() {
	stbi_image_free(m_LocalBuffer);

    XFreePixmap(display, double_buffer);
	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

#endif
