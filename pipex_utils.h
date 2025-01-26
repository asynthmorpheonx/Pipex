/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:17:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/26 01:18:43 by mel-mouh         ###   ########.fr       */
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

typedef struct s_struct
{
	int				**pipes;
	int				in_file;
	int				out_file;
	int				cmd_count;
	int				pipe_count;
	pid_t			*pids;
}	t_container;

size_t	ft_strlen(const char *str);
void	ft_putendl_fd(char *s1, char *s2, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_close(int *pip);
char	**ft_split(char const *s, char c);
char	*searcher(char **envp);
char	*extract_path(char **path, char *cmd);
void	ft_free(char **strs1, char **strs2);
void	firstchild_exec(int *pip, char **argv, char **envp);
void	print_if_error(int the_error, char *probleme);
int		check_access(char **path, char *cmd);
char	*extract_path(char **path, char *cmd);
void	handler(char **path, char **arg);
void	init_nd_execute(char **arg, char **envp);
void	secchild_exec(int *pip, char **argv, char **envp);

#endif