#ifndef VAR_H
#define VAR_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

// TODO: Not rely on this mess. i dont like it

static Display *display;
static XImage *image;
static Window window;
static GC gc;
static XWindowAttributes wa;	
static unsigned char *m_LocalBuffer;
static Pixmap double_buffer;
static Atom wm_delete_window;
static KeySym key;

static int win_Width;
static int win_Height;

static int m_Width;
static int m_Height; 
static int m_BPP;

static int image_x  = 0;
static int image_y  = 0;
static int source_x = 0;
static int source_y = 0;

static int speed = 25;

#endif 
