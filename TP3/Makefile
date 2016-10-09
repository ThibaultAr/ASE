#ROOTDIR=/home/dubois/FIL/M1S1/ASE/libhardware
ROOTDIR=/home/enseign/ASE

CC = gcc
CFLAGS = -m32
CFLAGS += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

ALL = ctx.o pingpong

compile: $(ALL)

ctx.o : ctx.c ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

pingpong.o : pingpong.c ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

pingpong: pingpong.o ctx.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.o *.s $(ALL) *.bin
