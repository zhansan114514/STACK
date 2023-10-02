LDLIBS = -lreadline
CFLAGS += -I/usr/include/readline

myprogram: main3.o stack.o stack2.o
	cc -o myprogram main3.o stack.o stack2.o $(LDLIBS)

main3.o: main3.c stack.h stack.c stack2.c
	cc -c main3.c $(CFLAGS)

stack.o: stack.c stack.h
	cc -c stack.c $(CFLAGS)

stack2.o: stack2.c stack.h
	cc -c stack2.c $(CFLAGS)

clean:
	rm -f myprogram main3.o stack.o stack2.o
