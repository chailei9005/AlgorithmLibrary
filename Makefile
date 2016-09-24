SRCDIR := src
BUILDDIR := build
TARGET := ./AlgorithmTest.out

SRCEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

CC := g++ -std=c++11 -O2

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) -c $< -o $@ 

clean:
	@rm -rf $(BUILDDIR) $(TARGET)

run:
	@$(TARGET)

.PHONY: clean run