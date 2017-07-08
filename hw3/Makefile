CC = g++
CFLAGS = -o
CFLAGS1 = -O3
CFLAGS2 = -std=c++11
ONAME = hw3.o

hw3: ${ONAME}
	${CC} ${ONAME} ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c ${CFLAGS1}

.PHONY: run, clean
run:
	@./hw3
clean:
	@rm -rf *.o
