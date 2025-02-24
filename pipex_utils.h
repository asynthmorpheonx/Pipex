/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:17:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 19:02:50 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <error.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_util
{
	int		in_file;
	int		out_file;
	int		*pipe;
	char	**envp;
	char	**av;
}	t_utils;

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	print_if_error(int the_error, char *probleme);
char	*ft_strjoin(char const *s1, char const *s2);
void	safer_fork(pid_t *pids, t_utils *container);
t_utils	*init_it(char **av, char **envp, int *pip);
void	ft_putendl_fd(char *s1, char *s2, int fd);
void	init_nd_execute(char **arg, char **envp);
char	*extract_path(char **path, char *cmd);
void	child_exec(t_utils *container, int i);
void	wait_twice(int	*status, pid_t *pids);
int		check_access(char **path, char *cmd);
void	ft_free(char **strs1, char **strs2);
char	*ft_strchr(const char *str, int c);
char	**ft_split(char const *s, char c);
size_t	ft_strch(const char *str, int c);
void	handler(char **path, char **arg);
void	close_node(t_utils *container);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*searcher(char **envp);
void	ft_close(int *pip);

#endif