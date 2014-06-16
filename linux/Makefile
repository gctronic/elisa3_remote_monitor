TARGET = main
CC = gcc
ifeq ($(shell uname), Darwin)
CFLAGS = -O2 -I../../pc-side-elisa3-library -L/opt/local/lib/ -L../../pc-side-elisa3-library/linux/ -lelisa3 -lm -lusb-1.0 -lpthread -lncurses
else
CFLAGS = -O2 -I../../pc-side-elisa3-library -L/usr/lib/i386-linux-gnu/ -L../../pc-side-elisa3-library/linux/ -lelisa3 -lm -lusb-1.0 -lpthread -lncurses
endif

SRC = ../main.c
OBJS = terminal.o input.o

all: $(OBJS)
		$(CC) $(SRC)  $(OBJS) $(CFLAGS) -o $(TARGET)

terminal.o: ../terminal.h ../terminal.c
		$(CC) -c ../terminal.c $(CFLAGS) 

input.o:  ../input.h ../input.c
		$(CC) -c ../input.c $(CFLAGS) 

clean:
		rm -f $(TARGET)
		rm *.o

