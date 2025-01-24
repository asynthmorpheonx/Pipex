CFILES = utils.c ft_split.c ft_strjoin.c ft_strnstr.c searcher.c ft_putendl_fd.c
OFILES = $(CFILES:.c=.o)
NAME = pipex
LIBNAME = libpipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(LIBNAME)


$(LIBNAME): $(OFILES)
	@ar rcs $(LIBNAME) $(OFILES)
	@$(CC) $(CFLAGS) pipex.c  $(LIBNAME) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OFILES) $(LIBNAME)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
