/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:32:30 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/11 23:52:30 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **strs1, char **strs2)
{
	int	i;

	i = 0;
	if (strs1)
	{
		while (strs1[i])
		{
			free(strs1[i]);
			i++;
		}
		free(strs1);
	}
	if (!strs2)
		return ;
	i = 0;
	while (strs2[i])
	{
		free(strs2[i]);
		i++;
	}
	free(strs2);
}
