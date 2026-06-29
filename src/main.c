#define STB_IMAGE_IMPLEMENTATION
#include <string.h>
#include <err.h>

#include "events.h"

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
	else err(1, "Invalid filetype. Try something called an image");
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

    MageInit(&argv[1]);

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

    int running = 1;
	while (running) {
        XEvent event;
        if (!RenderEvents(event)) {
            running = 0;
        }
	}

    MageQuit();
	return 0;
}
