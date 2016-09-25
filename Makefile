BUILDDIR := build
$(shell mkdir -p $(BUILDDIR))

SRCDIR := src
SRCEXT := cpp
TARGET := ./AlgorithmTest.out

SRCFILES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SRCFILES:.$(SRCEXT)=.o))

CC := g++ -std=c++11 -O2

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) -c $< -o $@ 

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

run:
	@$(TARGET)

.PHONY: clean run