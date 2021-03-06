CC = g++

CFLAGS = -march=native -pipe -std=gnu++20 -pedantic -Wall -Wextra -Werror
LDLIBS = -pthread

INCLUDE_PATH = ./includes

TARGET       = chess
FILEXT       = cpp

SRCDIR       = src
OBJDIR       = obj
BINDIR       = bin

SOURCES     := $(wildcard $(SRCDIR)/*.$(FILEXT))
INCLUDES    := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS     := $(SOURCES:$(SRCDIR)/%.$(FILEXT)=$(OBJDIR)/%.o)

PATH_TO_EXE  = $(BINDIR)/$(TARGET)

all : release docs

.PHONY : docs
docs:
	@echo "\033[95mBuilding documentation...\033[0m"
	@mkdir -p html/assets
	@cp -r assets/* html/assets
	@doxygen ./Doxyfile > /dev/null 2>&1
	@echo "\033[97mDocumentation built!\033[0m"

debug: CFLAGS += -Og -DDEBUG -g -ggdb
debug: $(PATH_TO_EXE)
	@echo "\033[93mRunning in debug mode!\033[0m"

release: CFLAGS += -Ofast
release: $(PATH_TO_EXE)
	@echo "\033[96mRunning in release mode!\033[0m"

run:
ifneq ("$(wildcard $(PATH_TO_EXE))", "")
	./$(PATH_TO_EXE)
else
	@echo "\033[91mNo executable found!\033[0m"
endif

run-release: release
	./$(PATH_TO_EXE)

run-debug: debug
	valgrind --leak-check=full --show-leak-kinds=all --vgdb=full -s ./$(PATH_TO_EXE)

$(PATH_TO_EXE): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mLinking complete!\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.$(FILEXT) $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(PATH_TO_EXE)
