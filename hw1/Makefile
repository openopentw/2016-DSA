CC = g++
CFLAGS = -o

hw1: hw1.o
	${CC} hw1.o ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c

.PHONY: run, clean
run:
	@./hw1
clean:
	@rm -rf *.o
