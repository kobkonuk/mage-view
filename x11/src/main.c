#define STB_IMAGE_IMPLEMENTATION
#include <X11/Xlib.h>

#include <string.h>
#include <err.h>

#include "events.h"
#include "var.h"

typedef struct {	
	const char *jpg;
	const char *jpeg;
	const char *png;
} Filetype;

Filetype filetype = {
	.jpg  = ".jpg",
	.jpeg = ".jpeg",
	.png  = ".png"
};

const char *GetFileType(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(dot) return dot;
	else err(1, "Invalid filetype. Try something called an 'image'");
}

int main (int argc, char *argv[]) 
{
	if (argc == 1) {
		err(1, "Please provide a filepath to your desired image");
	}

	const char *type = GetFileType(argv[1]);
	
	if (strcmp(type, filetype.jpg) == 0);
	else if (strcmp(type, filetype.jpeg) == 0);
	else if (strcmp(type, filetype.png) == 0);
	else err(1, "Invalid filetype. Only JPEGs and PNGs are supported");	

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

    XSetWindowBackgroundPixmap(display, window, None);
    XStoreName(display, window, "mage-view"); // thanks choketa

	inverse(); 
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

    XEvent event;
    
    int running = 1;
	while (running) {
        while (XPending(display)) {
            XNextEvent(display, &event);
            
            if (!RenderEvents(event)) { // events.h
                running = 0;
            }
        }
	}

    MageQuit();
	return 0;
}
