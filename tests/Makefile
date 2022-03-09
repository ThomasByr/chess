CC = g++-11
TARGET = tests

CFLAGS = -march=native -Og -pipe -std=c++20 -pedantic -Wall -Wextra -Werror -DDEBUG -g
LDLIBS =

INCLUDE_PATH = ../includes

SRCDIR    = ../src
OBJDIR    = obj

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS0 := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS   = $(filter-out $(OBJDIR)/main.o,$(OBJECTS0))

tests: $(OBJECTS) obj/tests.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mLinking complete!\033[0m"
	@echo "\033[33mRunning in debug mode!\033[0m"

check: clean tests
	valgrind --leak-check=full --show-leak-kinds=all --vgdb=full -s ./$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)

obj/tests.o: tests.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(TARGET)
