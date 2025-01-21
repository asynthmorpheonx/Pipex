/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 23:34:06 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/21 20:28:41 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*str;

	if (!dest || !src)
		return (NULL);
	i = 0;
	dst = (unsigned char *)dest;
	str = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	str = ((char *)malloc(ft_strlen(s1) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	if (len == 0)
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}