
CFLAGS = -Wall

all: imt2b zoom

%.o: %.c
	gcc ${DFLAGS} -c -o $@ $<


imt2b: imt2b.o image.o
	gcc ${CFLAGS} -o imt2b $^

zoom: zoom.o image.o
	gcc ${CFLAGS} -o zoom $^
