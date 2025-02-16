CFILES = pipex.c print_errors.c searchers.c split_and_join.c utils.c utils_to_execute.c wait_init_nd_fork.c	dup_open_exece.c
BFILES = print_errors_bonus.c exec_handle_init_bonus.c handle_struct_bonus.c split_and_join_bonus.c \
	utils_to_execute_bonus.c get_next_line_bonus.c pipex_bonus.c searchers_bonus.c utils_bonus.c
OFILES = $(CFILES:.c=.o)
OBFILES = $(BFILES:.c=.o)
NAME = pipex
LIBNAME = libpipex.a
BONUSLIB = bonuslib.a
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(LIBNAME)

$(LIBNAME): $(OFILES)
	@ar rcs $(LIBNAME) $(OFILES)
	@$(CC) $(CFLAGS) pipex.c  $(LIBNAME) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUSLIB)

$(BONUSLIB): $(OBFILES)
	@ar rcs $(BONUSLIB) $(OBFILES)
	@$(CC) $(CFLAGS) pipex_bonus.c  $(BONUSLIB) -o $(NAME)

clean:
	rm -rf $(OFILES) $(LIBNAME) $(BONUSLIB) $(OBFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus