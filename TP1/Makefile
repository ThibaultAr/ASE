ALL = try_mul

compile: $(ALL)

try.o : try.c try.h
	gcc -m32 -c $<

try_mul.o : try_mul.c try.h
	gcc -m32 -c $<

try_mul: try_mul.o try.o
	gcc -m32 $^ -o $@

clean:
	rm -f *.o *.s $(ALL)
