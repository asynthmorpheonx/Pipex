CFILES = utils.c split_and_join.c utils_to_execute.c searchers.c print_errors.c
OFILES = $(CFILES:.c=.o)
NAME = pipex
LIBNAME = libpipex.a
BONUSLIB = bonuslib.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(LIBNAME)


$(LIBNAME): $(OFILES)
	@ar rcs $(LIBNAME) $(OFILES)
	@$(CC) $(CFLAGS) pipex.c  $(LIBNAME) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OFILES)
	@ar rcs $(BONUSLIB) $(OFILES)
	@$(CC) $(CFLAGS) pipex_bonus.c  $(BONUSLIB) -o $(NAME)

clean:
	@rm -rf $(OFILES) $(LIBNAME) $(BONUSLIB)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
