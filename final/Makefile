.PHONY : all clean
all = tmSnow
CFLAGS =-Wall -pedantic -ansi
LIBS = -lm

tmSnow: bitmap.o tmSnow.o
	gcc -o $@ $^ $(LIBS)

clean:
	rm tmSnow
