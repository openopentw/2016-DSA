CC = g++
CFLAGS = -o

main: main.o
	${CC} main.o ${CFLAGS} $@
%.o: %.cc
	${CC} $< -c

.PHONY: run, clean
run:
	@./main
clean:
	@rm -rf *.o
