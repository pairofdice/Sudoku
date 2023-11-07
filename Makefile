
NAME=sudoku

OBJECTS=sudoku.o print.o
OBJDIRS=./obj/
INCDIRS=. ./inc/
INCLUDES=$(foreach D,$(INCDIRS),-I$(D))
CFLAGS=-O -Wall -Wextra -Werror -pedantic -ansi -std=c11 $(INCLUDES)
CC=gcc

# Targets that do not refer to files but are just actions are called phony targets
.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJECTS) $(NAME)

# $@ = target name
# $? = prerequisites that are newer than target
# $% = target member name: with target foo.a(bar.o), $% will expand to bar.o, $@ would be foo.a
# $< = first prerequisite
# $^ = all prerequisites
# $| = order only prerequisites
# $* = the stem of an implicit match, with target dir/a.foo.b   --- and target patter

# Implicit rules
# n.o is made automatically from n.c with command like: $(CC) -c $(CPPFLAGS)
# n is made automatically from n.o: $(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Variables used by implicit rules
# CC 		--- c compiler, default cc
# CXX		--- cpp compiler, default f++
# CFLAGS	--- Extra flags to give the compiler
# CXXFLAGS
# CPPFLAGS	--- Extra flags for the C preprocessor
# LDFLAGS	--- Flags for linking
