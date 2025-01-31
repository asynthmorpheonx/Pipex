/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_execute_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 00:28:39 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:23:16 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

char	*extract_path(char **path, char *cmd)
{
	char	*temp;
	char	*str;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0
		&& (cmd[0] == '/' || cmd[0] == '~' || cmd[0] == '.'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		str = ft_strjoin(temp, cmd);
		if (access(str, X_OK | F_OK) == 0)
			return (free(temp), str);
		free(temp);
		free(str);
		i++;
	}
	return (NULL);
}

int	check_access(char **path, char *cmd)
{
	char	*str;

	if (cmd[0] == '/' || cmd[0] == '~' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (0);
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
			return (126);
	}
	if (!path)
		return (127);
	str = extract_path(path, cmd);
	if (str)
	{
		if (access(str, X_OK) == 0)
			return (free(str), 0);
		return (free(str), 126);
	}
	return (free(str), 127);
}

void	handler(char **path, char **arg)
{
	int		access_status;

	access_status = check_access(path, arg[0]);
	print_if_error(access_status, arg[0]);
	ft_free(path, arg);
	exit(access_status);
}

void	init_nd_execute(char **arg, char **envp)
{
	char	**path;
	char	*cmd;

	path = NULL;
	cmd = NULL;
	if (!arg[0] || !arg[0])
	{
		print_if_error(127, "' '");
		ft_free(arg, NULL);
		exit(127);
	}
	if (envp)
		path = ft_split(searcher(envp), ':');
	cmd = extract_path(path, arg[0]);
	if (!cmd)
		handler(path, arg);
	execve(cmd, arg, envp);
	print_if_error(127, arg[0]);
	ft_free(arg, path);
	free(cmd);
	exit(2);
}
