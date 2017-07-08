CC = g++
CFLAGS = -o
CFLAGS1 = -O3
CFLAGS2 = -std=c++11
ONAME = hw5.o

hw5: ${ONAME}
	${CC} ${ONAME} ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c ${CFLAGS1}

.PHONY: run, clean
run:
	@./hw5
clean:
	@rm -rf *.o
