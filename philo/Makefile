# Compiler settings.
CC = cc
CFLAGS = -Wall -Wextra -Werror
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

debug_only: CFLAGS += -g
debug_only: re