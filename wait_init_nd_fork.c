/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_init_nd_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:50:21 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:53:53 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

t_utils	*init_it(char **av, char **envp, int *pip)
{
	t_utils	*container;

	container = malloc(sizeof(t_utils));
	if (!container)
	{
		perror("malloc ");
		exit (1);
	}
	container->pipe = pip;
	container->envp = envp;
	container->av = av;
	return (container);
}

void	wait_twice(int	*status, pid_t *pids)
{
	waitpid(pids[0], status, 0);
	waitpid(pids[1], status, 0);
}

void	safer_fork(pid_t *pids, t_utils *container)
{
	pids[0] = fork();
	if (pids[0] == -1)
	{
		perror("fork ");
		free(container);
		exit(1);
	}
	else if (pids[0] == 0)
		child_exec(container, 1);
	pids[1] = fork();
	if (pids[1] == -1)
	{
		perror("fork ");
		free(container);
		exit(1);
	}
	else if (pids[1] == 0)
		child_exec(container, 2);
	close(container->pipe[1]);
}
