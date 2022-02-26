NAME=pipex
cc = gcc
flags = -Wall -Wextra -Werror
srcs = pipex.c\
	   utils.c\
	   ft_split.c\

objs = $(srcs:.c=.o)

all : $(NAME)

$(NAME): $(objs)
	ar rc $(NAME) $(objs)

%.o: %.c pipex.h
	$(cc) $(flags) -c $<  -o $@

clean :
	rm -rf $(objs)

fclean :	clean
	rm -rf	$(NAME)

re:	fclean all


.PHONY: all clean fclean re
