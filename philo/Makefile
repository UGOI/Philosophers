# Compiler settings.
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
LDFLAGS =

# Makefile settings.
APPNAME = philo
EXT = .c
LIBEXT = .a
SRCDIR = src
OBJDIR = obj
LIBDIR =
RLINEDIR = /usr/include/readline
SRC := $(shell find $(SRCDIR) -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

RM = rm -f
DELOBJ = $(OBJ)

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Building rule for .o files and its .c
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

# Rules
.PHONY: clean
clean:
	@$(RM) $(DELOBJ)

.PHONY: fclean
fclean: clean
	@$(RM) $(APPNAME)
.PHONY: re
re:	fclean all

debug: CFLAGS += -g -fsanitize=thread
debug: re

test1:
	./philo 1 800 200 200
test2:
	./philo 5 800 200 200
test3:
	./philo 5 800 200 200 7
	@printf "Num of meals for 1st philo: "
	@./philo 5 800 200 200 7 | grep "1 is eating" | wc -l
test4:
	./philo 4 410 200 200
test5:
	./philo 4 310 200 100
test6:
	./philo 2 100 200 200
test: test1 test2 test3 test4 test5 test6
.PHONY: test1 test2 test3 test4 test5 test6 test

