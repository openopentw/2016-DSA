CC = g++
CFLAGS = -o
CFLAGS1 = -O3
CFLAGS2 = -std=c++11
ONAME = hw6.o

hw6: ${ONAME}
	${CC} ${ONAME} ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c ${CFLAGS1}

.PHONY: run, clean
run:
	@./hw6
clean:
	@rm -rf *.o
