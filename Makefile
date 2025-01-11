CFILES = ft_free.c ft_split.c ft_strjoin.c ft_strnstr.c \
	ft_strdup.c ft_strlen.c ft_substr.c searcher.c ft_memcpy.c
OFILES = $(CFILES:.c=.o)
NAME = pipex
LIBNAME = libpipex.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBNAME)
	@$(CC) pipex.c $(LIBNAME) -o $(NAME)

$(LIBNAME): $(OFILES)
	@ar rcs $(LIBNAME) $(OFILES)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
