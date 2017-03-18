

DEBUG=no

C= gcc

# compiling flags here
CFLAGS	= -W -Wall -Wextra -Werror -I./includes/

# if debug is set to yes, add -g3 flag
ifeq ($(DEBUG),yes)
	CFLAGS += -g3
endif

# name of the projet
NAME   = philo

# use
COUNT=1
NBSOURCES= $(shell find src/ -type f -name '*.c' | wc -l)

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

# Sources, Includes and Objects
SOURCES  := 		$(wildcard $(SRCDIR)/*.c)
INCLUDES := 		$(wildcard includes/*.h)
OBJECTS  := 		$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RM       = 			rm -rf

$(BINDIR)/$(NAME):	$(OBJECTS)
			@$(C) -o $@ $(CFLAGS) $(OBJECTS) -L. -lriceferee -lpthread
			@echo "\033[94mProject $(NAME) build successfully!\033[0m"

$(OBJECTS):		$(OBJDIR)/%.o : $(SRCDIR)/%.c
			@mkdir -p $(dir $@)
			@$(C) $(CFLAGS) -c $< -o $@
			@echo "[\033[95m$(COUNT)\033[0m/\033[93m$(NBSOURCES)\033[0m][\033[92m$<\033[0m]"
			@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

all:			$(BINDIR)/$(NAME)

.PHONY:		 	clean

clean:
			@$(RM) $(OBJDIR)
			@echo "\033[93mCleanup complete!\033[0m"

.PHONY: 		fclean

fclean: 		clean
			@$(RM) $(BINDIR)/$(NAME)
			@echo "\033[93mExecutable removed!\033[0m"

re:			fclean $(BINDIR)/$(NAME)
