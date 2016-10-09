CC = gcc
CFLAGS = -m32
CFLAGS += -g

ALL = ctx.o pingpong

compile: $(ALL)

ctx.o : ctx.c ctx.h
	$(CC) $(CFLAGS) -c $<

pingpong.o : pingpong.c ctx.h
	$(CC) $(CFLAGS) -c $<

pingpong: pingpong.o ctx.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.s $(ALL)
