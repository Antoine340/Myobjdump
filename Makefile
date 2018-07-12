##
## Makefile for objdump in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
## 
## Made by chauvin
## Login   <chauvi_d>
## 
## Started on  Sun Feb 26 21:44:21 2017 chauvin
## Last update Sun Feb 26 22:18:36 2017 chauvin
##

SRCS_NM		=	my_nm.c \

NAME_NM		=	my_nm

SRCS_OBJ	=	my_objdump.c \
			my_obj64.c \
			my_obj32.c \
			print_64.c \
			print_32.c \
			check_error.c \

NAME_OBJ	=	my_objdump

CC		=	gcc

CFLAGS		=	-W -Wall -Wextra -Werror -I./Include

OBJS_NM		=	$(SRCS_NM:.c=.o)

OBJS_OBJ	=	$(SRCS_OBJ:.c=.o)

RM		=	rm -f

all: nm objdump

$(NAME_NM): $(OBJS_NM)
	$(CC) $(OBJS_NM) $(FLAGS) -o $(NAME_NM)

$(NAME_OBJ): $(OBJS_OBJ)
	$(CC) $(OBJS_OBJ) $(FLAGS) -o $(NAME_OBJ)

nm: $(NAME_NM)

objdump: $(NAME_OBJ)

clean:
	$(RM) $(OBJS_NM)
	$(RM) $(OBJS_OBJ)

fclean: clean
	$(RM) $(NAME_NM) $(OBJS_NM)
	$(RM) $(NAME_OBJ) $(OBJS_OBJ)

re: fclean all

.PHONY: all clean fclean re
