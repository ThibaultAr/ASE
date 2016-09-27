ALL = ctx.o pingpong

compile: $(ALL)

ctx.o : ctx.c ctx.h
	gcc -m32 -c $<

pingpong.o : pingpong.c ctx.h
		gcc -m32 -c $<

pingpong: pingpong.o ctx.o
	gcc -m32 $^ -o $@

clean:
	rm -f *.o *.s $(ALL)
