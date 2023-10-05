LDLIBS = -lreadline
CFLAGS += -I/usr/include/readline

myprogram: main3.o stack.o stack2.o binary.o hex.o
	cc -o myprogram main3.o stack.o stack2.o binary.o hex.o $(LDLIBS)

main3.o: main3.c stack.h stack.c stack2.c binary.o hex.o
	cc -c main3.c $(CFLAGS)

stack.o: stack.c stack.h
	cc -c stack.c $(CFLAGS)

stack2.o: stack2.c stack.h
	cc -c stack2.c $(CFLAGS)

binary.o: stack.c stack.h binary.c
	cc -c binary.c $(CFLAGS)

hex.o: stack.c stack.h hex.c 
	cc -c hex.c $(CFLAGS)
clean:
	rm -f myprogram main3.o stack.o stack2.o binary.o hex.c
