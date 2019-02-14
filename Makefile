##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

INC	=	-I ./inc

SRCDIR	= ./src/

NM_SRCS	=	nm/section_utils64.c	\
			nm/section_utils32.c	\
			nm/sort_symbols.c	\
			nm/type32.c	\
			nm/type64.c	\
			nm/nm.c	\
			manage_error.c

OBJDUMP_SRCS	=	objdump.c

CFLAGS	=	-Wall -g $(INC)#-Wextra

NM_PREFIX_SRCS 		= $(addprefix $(SRCDIR), $(NM_SRCS))
OBJDUMP_PREFIX_SRCS = $(addprefix $(SRCDIR), $(OBJDUMP_SRCS))

NM_OBJS			=	$(NM_PREFIX_SRCS:.c=.o)
OBJDUMP_OBJS	=	$(OBJDUMP_PREFIX_SRCS:.c=.o)

NM_NAME			=	my_nm
OBJDUMP_NAME	=	my_objdump

all:	$(NM_NAME) $(OBJDUMP_NAME)

$(NM_NAME):	$(NM_OBJS)
	@printf 'FLAGS: $(LDFLAGS) $(CFLAGS)\n'
	@printf 'Create: ./$(NM_NAME)\n'
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDUMP_NAME):	$(OBJDUMP_OBJS)
	@printf 'FLAGS: $(LDFLAGS) $(CFLAGS)\n'
	@printf 'Create: ./$(OBJDUMP_NAME)\n'
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o:	%.c
	@printf '[OK] Building: $<\n'
	@$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@rm -f $(NM_OBJS)
	@rm -f $(OBJDUMP_OBJS)
	@printf 'Clean : OK\n'

fclean: clean
	@rm -f $(NM_NAME)
	@rm -f $(OBJDUMP_NAME)
	@printf 'Fclean: ./$(NAME)\n'

re: fclean all

.PHONY: all fclean re
