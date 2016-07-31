OBJS = main.o DisjointSet.o ArithmeticExpression.o RandomEngine.o \
Graph.o Algorithm.o AlgorithmGraph.o NPuzzle.o

CC = g++ -std=c++11

APP_NAME = demo

$(APP_NAME): $(OBJS)
	$(CC) -o $(APP_NAME) $(OBJS)

$(OBJS): %.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm $(APP_NAME) ${OBJS}

run:
	@./$(APP_NAME)
