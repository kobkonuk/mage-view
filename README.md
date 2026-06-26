**NOTE**

image will no longer center when you resize/move the window. Just press c. its not that hard. get over it.

(There was a bug where bigger images would lag a lot when resizing windows because center() would be called so often. I decided it doesnt have to be that way eitherway)

XEvent.type == ConfigureNotify will now only do some double buffer stuff, implemented by Choketa

.

The performance is also shit. I dont know why, maybe im just fucking stupid. i tried to use feh to compare my project to it but i just felt depressed. 

(feh has wayy better performance, especially bigger images)

WHy is it lagging!@!???? Any Xlib professionals??? Im sure its not an x11 issue(Not like I can just go 'lower level' anyways) 

.


**THANKS TO**
Chocketa who fixed my flickering issue. Shout out to my boy


```
mage <filepath>
```

Idk how to implement dragging the image with your mouse. Xlib documentation is really confusing.

im also too stubborn to try out xcb... im already too deep...


**CONTROLS**

arrow keys = moves the image by 25 pixels

press c = centers the image

press enter = you will find out....
