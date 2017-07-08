CC = g++
CFLAGS = -O3
CFLAGS2 = -std=c++11
PROG = hw4
OBJS = hw4.o

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $@
%.o: %.cc
	$(CC) $< -c $(CFLAGS)

.PHONY: run, clean
run:
	@./$(PROG)
clean:
	@rm -rf *.o
