LIBS = `pkg-config --libs gtk+-3.0`

CFLAGS = `pkg-config --cflags gtk+-3.0`

all: application

application: main.c application.c application.h main.h
	gcc -o application main.c application.c application.h $(LIBS) $(CFLAGS) -lwiringPi
