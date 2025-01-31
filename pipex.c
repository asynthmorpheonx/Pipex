/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:51:26 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pids[2];
	t_utils	*container;

	if (argc != 5)
	{
		ft_putendl_fd("syntax error :", "./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe ");
		exit (1);
	}
	container = init_it(argv, envp, fd);
	safer_fork(pids, container);
	close_node(container);
	wait_twice(&status, pids);
	free(container);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
