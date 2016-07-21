OBJS = main.o DisjointSet.o
CC = g++ -std=c++11
APP_NAME = demo

demo: $(OBJS)
	$(CC) -o $(APP_NAME) $(OBJS)

$(OBJS): %.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm $(APP_NAME) ${OBJS}

run:
	@./$(APP_NAME)
