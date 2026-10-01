**simple image viewer**

Despite it being named "mage" sort of implying that it "works like magic" I think this it actually works like shit. I plan for this to have all sorts of maybe useless features, as long as they are easy to implement.

```
mage <filepath>
```


**building**

```
make opengl
```

or for windows:
```
make opengl-win
```
you will need mingw stuff set up for make, xxd and gcc.
I am planning to get dat shit easier to compile on windows
But who doesnt use WSL anyways


**NOTE**

WILL NOW MAINLY BE OPENGL FOCUSED!!!! I DONT LIKE XLIB!!!!

if you start programming before compiling, you would get the error that glfw-opengl/src/glsl.h doesn't exist. just compile and then everything will be fine

or manually:

xxd -i res/shaders/shader.glsl > glfw-opengl/src/glsl.h

**CONTROLS** things marked -G: is not present in the opengl version, -X for missing in x11

-G: press c = centers the image // though both will be simple to implement

-X: press space = stretch n scale

-X: press i = zoom in
-X: press o = zoom out

arrow keys/wasd = moves the image
press enter = you will find out....



**TODO**

a way to "hide" the nuklear thingymabob with a keybind so that you can fully focus on the image

Fit image, fill image and a center command

fix zoom

**THANKS TO**
Chocketa who fixed my xlib flickering issue. Shout out to my boy
