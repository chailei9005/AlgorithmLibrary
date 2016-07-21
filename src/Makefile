# Objects
OBJS = main.o DisjointSet.o

# Compiler
CC = g++ -std=c++11

demo: $(OBJS)
	$(CC) -o demo $(OBJS)

%.o: %.c

clean:
	rm demo ${OBJS}

run:
	@./demo