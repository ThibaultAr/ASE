# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

#ROOTDIR=/home/dubois/FIL/M1S1/ASE/libhardware
ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic -m32
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= mkhd vm mknfs alloclib
OBJECTS	= $(addsuffix .o,\
	  mkhd)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules
###------------------------------------------------------------
mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mkhd: mkhd.o drive.o
	$(CC) $(CFLAGS) -o mkhd $^ $(LIBS)

drive.o: drive.c drive.h
	$(CC) $(CFLAGS) -c drive.c $(INCDIR)

mbr.o: mbr.c mbr.h drive.h
	$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

mkvol.o: mkvol.c mbr.h
	$(CC) $(CFLAGS) -c mkvol.c $(INCDIR)

mkvol: mkvol.o mbr.o
	$(CC) $(CFLAGS) -o mkvol $^ $(LIBS)

tools.o: tools.c
	$(CC) $(CFLAGS) -c tools.c $(INCDIR)

current.o: current.c tools.h bloc.h
	$(CC) $(CFLAGS) -c current.c $(INCDIR)

bloc.o: bloc.c mbr.h
	$(CC) $(CFLAGS) -c bloc.c $(INCDIR)

mknfs.o: mknfs.c
	$(CC) $(CFLAGS) -c mknfs.c $(INCDIR)

alloclib.o: alloclib.c
	$(CC) $(CFLAGS) -c alloclib.c $(INCDIR)

vm.o: vm.c
	$(CC) $(CFLAGS) -c vm.c $(INCDIR)

vm: vm.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

mknfs: mknfs.o mbr.o drive.o bloc.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

alloclib: alloclib.o mbr.o drive.o bloc.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
