#ROOTDIR=/home/dubois/FIL/M1S1/ASE/libhardware
ROOTDIR=/home/enseign/ASE

CC = gcc
CFLAGS = -m32
CFLAGS += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

ALL = ctx.o sem.o pingpong prodcons

compile: $(ALL)

depend :
	$(CC) -MM $(CFLAGS) $(INCS) *.c

ctx.o : ctx.c ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

sem.o : sem.c sem.h ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

pingpong.o : pingpong.c ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

pingpong: pingpong.o ctx.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

prodcons.o : prodcons.c sem.h ctx.h
	$(CC) $(CFLAGS) $(INCS) -c $<

prodcons: prodcons.o sem.o ctx.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.o *.s $(ALL) *.bin *.txt
