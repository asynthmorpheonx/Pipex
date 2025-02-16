/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:17:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 19:30:44 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_BONUS_H
# define PIPEX_UTILS_BONUS_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <error.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# define BUFFER_SIZE 1

typedef struct s_struct
{
	int				**pipes;
	int				in_file;
	int				out_file;
	int				pipe_count;
	int				is_there_heredoc;
	int				cmd_count;
	pid_t			*pids;
}	t_box;

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	forking_for_executing(t_box *container, char **av, char **envp);
void	child_execute(t_box *container, char **av, int i, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	open_a_file(t_box *container, char **av, int i);
void	wait_all_childs(t_box *container, int *status);
void	print_if_error(int the_error, char *probleme);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putendl_fd(char *s1, char *s2, int fd);
void	init_nd_execute_b(char **arg, char **envp);
char	*extract_path(char **path, char *cmd);
int		check_access(char **path, char *cmd);
void	ft_free(char **strs1, char **strs2);
t_box	*init_t_box(int argc, int heredoc);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char const *s, char c);
size_t	ft_strch(const char *str, int c);
void	handler(char **path, char **arg);
void	close_pipes(t_box *container);
void	free_pipes(t_box *container);
void	free_t_box(t_box *container);
void	make_pipes(t_box *container);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*searcher(char **envp);
void	ft_close(int *pip);

#endif