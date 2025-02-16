/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:26:49 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 19:30:22 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

static void	double_free(char **s1, char **s2)
{
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
}

static void	handle_here_doc(char *av, t_box **container)
{
	char	*input;
	char	*temp;

	while (1)
	{
		write(1, "heredoc>", 8);
		input = get_next_line(0);
		if (input)
			temp = ft_strjoin(av, "\n");
		if (!ft_strncmp(temp, input, ft_strlen(temp)) || !input)
		{
			if (!input)
				ft_putendl_fd("pipex: warning: ",
					"here-document at some line delimited by end-of-file", 2);
			else
				double_free(&temp, &input);
			break ;
		}
		write((*container)->pipes[0][1], input, ft_strlen(input));
		double_free(&temp, &input);
	}
	close((*container)->pipes[0][1]);
	get_next_line(-1);
}

int	main(int ac, char **av, char **envp)
{
	t_box	*container;
	int		status;

	status = 0;
	if (ac < 5)
		return (ft_putendl_fd("syntax error :",
				"./pipex infile cmd1 cmd2 ... outfile", 2), 1);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		container = init_t_box(ac, 1);
		handle_here_doc(av[2], &container);
	}
	else
		container = init_t_box(ac, 0);
	forking_for_executing(container, av, envp);
	wait_all_childs(container, &status);
	free_t_box(container);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
