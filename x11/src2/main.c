#define STB_IMAGE_IMPLEMENTATION
#include <X11/Xlib.h>
#include "../../vendor/stb_image.h"
#include "cli.h"
#include "var.h"
#include "render.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Please provide a path to an image");
        return 1;
    }

    if (!image_lowk_valid(argv)) {
        return 1;
    }

    XEvent event;
    
    bool running = 1;
	while (running) {
        while (XPending(display)) {
            XNextEvent(display, &event); 
            if (!RenderEvents(event)) { // events.h
                running = false;
            }
        }
	}

    stbi_image_free(m_LocalBuffer);
    XFreePixmap(display, double_buffer);
	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	XCloseDisplay(display);

    return 0;
}
