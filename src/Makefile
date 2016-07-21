# Objects
OBJS = main.o 

# Compiler
CC = g++ -std=c++11

demo: $(OBJS)
	$(CC) -o demo $(OBJS)

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm demo ${OBJS}

run:
	./demo