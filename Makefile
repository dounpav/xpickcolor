all:
	gcc xpickcolor.c -o xpickcolor -lX11 -Wall -Wextra

clean:
	rm xpickcolor
