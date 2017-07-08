CC = g++
CFLAGS = -o
CFLAGS1 = -O3
CFLAGS2 = -std=c++11

hw2: hw2.o
	${CC} hw2.o ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c ${CFLAGS1}

.PHONY: run, clean
run:
	@./hw2
clean:
	@rm -rf *.o
