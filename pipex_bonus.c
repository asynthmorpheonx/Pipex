/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:26:49 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/27 18:28:34 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	close_pipes(t_box *container)
{
	int	i;

	i = 0;
	while(i < container->pipe_count)
	{
		close(container->pipes[i][0]);
		close(container->pipes[i][1]);
		i++;
	}
}

void	free_pipes(t_box *container)
{
	int	i;

	i = 0;
	while(i < container->pipe_count)
	{
		free(container->pipes[i]);
		i++;
	}
	free(container->pipes);
}

void	free_t_box(t_box *container)
{
	close_pipes(container);
	free_pipes(container);
	free(container->pids);
	free(container);
}

void	open_a_file(t_box *container, char **av, int i)
{
	if (i == 0)
	{
		container->in_file = open(av[i], O_RDONLY);
		if (container->in_file == -1)
		{
			print_if_error(2, av[i]);
			free_t_box(container);
			exit(2);
		}
	}
	else if (i == container->pipe_count)
	{
		container->out_file = open(av[i + 3], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (container->out_file == -1)
		{
			print_if_error(126, av[i + 3]);
			free_t_box(container);
			exit(126);
		}
	}
}

void	child_execute(t_box *container, char **av, int i, char **envp)
{
	open_a_file(container, av, i);
	if (i == 0)
	{
		dup2(container->in_file, 0);
		dup2(container->pipes[i][1], 1);
		close(container->in_file);
		close(container->pipes[i][1]);
	}
	else if (i == container->pipe_count)
	{
		dup2(container->out_file, 1);
		dup2(container->pipes[i - 1][0], 0);
		close(container->out_file);
		close(container->pipes[i - 1][0]);
	}
	else
	{
		dup2(container->pipes[i - 1][0], 0);
		dup2(container->pipes[i][1], 1);
		close(container->pipes[i - 1][0]);
		close(container->pipes[i][1]);
	}
	init_nd_execute(ft_split(av[i + 2], ' '), envp);
}

void	make_pipes(t_box *container)
{
	int	i;

	i = 0;
	while (i < container->pipe_count)
	{
		container->pipes[i] = malloc(sizeof(int) * 2);
		if (!container->pipes[i] || pipe(container->pipes[i]) == -1)
			exit (1);
		i++;
	}
}

t_box	*init_t_box(int argc)
{
	t_box *container;

	container = malloc(sizeof(t_box));
	if (!container)
	{
		ft_putendl_fd("error :", "malloc failed while allocating", 2);
		exit(1);
	}
	container->pipe_count = argc - 4;
	container->pipes = malloc(sizeof(int *) * container->pipe_count);
	container->pids = malloc(sizeof(pid_t) * (argc - 3));
	if (!container->pipes || !container->pids)
	{
		ft_putendl_fd("error :", "malloc failed while allocating", 2);
		exit(1);
	}
	make_pipes(container);
	return (container);
}

void	wait_all_childs(t_box *container, int *status)
{
	int	i;

	i = 0;
	while (i < container->pipe_count + 1)
	{
		waitpid(container->pids[i], &status[0], 0);
		i++;
	}
}

void	forking_for_executing(t_box *container, char **av, char **envp)
{
	int	i;

	i = 0;
	while (i < container->pipe_count + 1)
	{
		container->pids[i] = fork();
		if (container->pids[i] == -1)
			exit (1);
		else if (container->pids[i] == 0)
			child_execute(container, av, i, envp);
		if (i > 0)
			close(container->pipes[i - 1][0]);
		if (i < container->pipe_count)
			close(container->pipes[i][1]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_box	*container;
	int		status;

	if (ac < 5)
		return (ft_putendl_fd("syntax error :", "./pipex infile cmd1 cmd2 ... outfile", 2), 1);
	container = init_t_box(ac);
	forking_for_executing(container, av, envp);
	wait_all_childs(container, &status);
	free_t_box(container);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
