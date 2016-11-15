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

BINARIES= mkhd vm mknfs alloclib if_pfile if_nfile if_cfile if_dfile
OBJECTS	= $(addsuffix .o,\
	  tools ifile mount)

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
### Binaries
###------------------------------------------------------------
if_cfile : if_cfile.o $(OBJECTS)
if_nfile : if_nfile.o $(OBJECTS)
if_dfile : if_dfile.o $(OBJECTS)
if_pfile : if_pfile.o $(OBJECTS)

% : %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

###------------------------------
### #include dependences
###------------------------------------------------------------
# you may fill these lines with "make depend"
if_cfile.o: if_cfile.c ifile.h bloc.h tools.h mount.h
if_dfile.o: if_dfile.c ifile.h bloc.h tools.h mount.h
if_nfile.o: if_nfile.c ifile.h bloc.h tools.h mount.h
if_pfile.o: if_pfile.c ifile.h bloc.h tools.h mount.h
ifile.o: ifile.c bloc.h tools.h ifile.h
mount.o: mount.c bloc.h
tools.o: tools.c tools.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
