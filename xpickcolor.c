/*
 * Original code: Barry Kauler
 * (bkhome.org/news/202110/get-the-colour-of-any-screen-pixel.html)
 *
 * Author: dounpav (Pavel Dounaev)
 */

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>

int main(void)
{
	int root_x;
	int root_y;
	unsigned int mask;
	Window root;
	XImage *image;

	/* Open the connection to the Xserver */
	Display *dpy = XOpenDisplay(NULL);

	if (dpy == NULL) {
		fprintf(stderr, "Unable to open connection to the Xserver\n");
		exit(EXIT_FAILURE);
	}

	/* Query mouse cursor's position */
	XQueryPointer(dpy, DefaultRootWindow(dpy),
			&root, &root,
			&root_x, &root_y,
			&root_x, &root_y,
			&mask);

	/* Retrive an image that the cursor is pointing to */
	image = XGetImage(dpy, XRootWindow(dpy, XDefaultScreen(dpy)),
			root_x, root_y, 1, 1, AllPlanes, XYPixmap);

	if (image == NULL) {
		fprintf(stderr, "Unable to get an image at position x: %d y: %d\n",
				root_x, root_y);
		XCloseDisplay(dpy);
		exit(EXIT_FAILURE);
	}

	unsigned long pixel = XGetPixel(image, 0, 0);
	fprintf(stdout, "#%06lx\n", pixel);

	XCloseDisplay(dpy);

	return 0;
}
