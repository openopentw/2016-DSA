CC = g++
CFLAGS = -o
CFLAGS1 = -O3
CFLAGS2 = -std=c++11
ONAME = final.o

final: ${ONAME}
	${CC} ${ONAME} ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c ${CFLAGS1}

.PHONY: run, clean
run:
	@./final
clean:
	@rm -rf *.o
