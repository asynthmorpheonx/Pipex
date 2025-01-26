/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/26 02:10:41 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	free_pipes(t_container *jmla)
{
    int	i;

    i = 0;
    while (i < jmla->pipe_count)
    {
        free(jmla->pipes[i]);
        i++;
    }
    free(jmla->pipes);
}

void	make_pipes(t_container *jmla)
{
	int	i;

	i = 0;
	while (i < jmla->pipe_count)
	{
		jmla->pipes[i] = malloc(2 * sizeof(int));
		if (!jmla->pipes[i] || pipe(jmla->pipes[i]) == -1)
		{
			free_pipes(jmla);
			free(jmla->pids);
			exit (1);
		}
		i++;
	}
}

void	close_pipes(t_container *jmla)
{
    int	i;

    i = 0;
    while (i < jmla->pipe_count)
    {
        close(jmla->pipes[i][0]);
        close(jmla->pipes[i][1]);
        i++;
    }
}

int	open_a_file(t_container *jmla, char **argv,int argc, int i)
{
	int fd;
	
	if (i == 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (jmla->in_file == -1)
		{
			print_if_error(2, argv[1]);
            close_pipes(jmla);
            free_pipes(jmla);
            exit(2);
		}
	}
	else if (i == jmla->pipe_count)
    {
        fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (jmla->out_file == -1)
        {
            print_if_error(126, argv[argc - 1]);
            close_pipes(jmla);
            free_pipes(jmla);
            exit(1);
        }
	}
	else
		return (-1);
	return (fd);
}

void	child_exec(t_container *jmla, char **argv, char **envp, int i, int argc)
{
    if (i == 0)
    {
        jmla->in_file = open_a_file(jmla, argv, argc, i);
        dup2(jmla->in_file, 0);
        dup2(jmla->pipes[i][1], 1);
    }
    else if (i == jmla->pipe_count)
    {
        jmla->out_file = open_a_file(jmla, argv, argc, i);
        dup2(jmla->pipes[i - 1][0], 0);
        dup2(jmla->out_file, 1);
    }
    else
    {
        dup2(jmla->pipes[i - 1][0], 0);
        dup2(jmla->pipes[i][1], 1);
    }
    close_pipes(jmla);
    init_nd_execute(ft_split(argv[i + 2], ' '), envp);
    exit(2);
}

t_container *init_bjmla(int argc)
{
    t_container	*jmla;

    jmla = malloc(sizeof(t_container));
	if (!jmla)
		exit(1);
	jmla->pipe_count = argc - 4;
    jmla->pipes = malloc(jmla->pipe_count * sizeof(int *));
    jmla->pids = malloc((jmla->pipe_count + 1) * sizeof(pid_t));
	if (!jmla->pipes || !jmla->pids)
        exit(1);
    make_pipes(jmla);
	return (jmla);
}

void	wait_all_childs(t_container *jmla, int *status)
{
	int	i;

	i = 0;
	while(i < jmla->pipe_count)
	{
		waitpid(jmla->pids[i], &status[0], 0);
		i++;
	}
}

void	free_containder(t_container *jmla)
{
	close_pipes(jmla);
	free_pipes(jmla);
	free(jmla->pids);
}

int	main(int argc, char **argv, char **envp)
{
    t_container	*jmla;
    int			status;
    int			i;

    if (argc < 5)
		return (1);
	jmla = init_bjmla(argc);
    i = 0;
    while (i < jmla->pipe_count + 1)
    {
        jmla->pids[i] = fork();
        if (jmla->pids[i] == -1)
            return (free_containder(jmla), 1);
        if (jmla->pids[i] == 0)
            child_exec(jmla, argv, envp, i, argc);
        i++;
    }
    close_pipes(jmla);
    wait_all_childs(jmla, &status);
    free_pipes(jmla);
    free(jmla->pids);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}
