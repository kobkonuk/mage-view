#ifndef INIT_H
#define INIT_H

#include <X11/Xlib.h>

#include "../../vendor/stb_image.h"
#include "var.h"

#include <stdbool.h>


bool init(const char *argv[]) {
    display = XOpenDisplay(NULL);
	if (display == NULL) {
        printf("XOpenDisplay Error");
        return false;
    }
    
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

    XSetWindowBackgroundPixmap(display, window, None);
    XStoreName(display, window, "mage-view"); // thanks choketa

	XGetWindowAttributes(display, window, &wa);

    image = XCreateImage(
			display,
			wa.visual,
			wa.depth,
			ZPixmap,
			0,
			m_LocalBuffer,
			m_Width,
			m_Height,
			32,
			m_Width * sizeof(int)
    );

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
            &wm_delete_window, 1
    );

	XSelectInput(display, window, 
			KeyPressMask | 
			ExposureMask |
			StructureNotifyMask
    );

	XMapWindow(display, window);

    return true;
}

#endif
