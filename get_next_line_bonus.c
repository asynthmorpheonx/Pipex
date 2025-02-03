/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:28:03 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 19:16:47 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

static char	*ft_memcpy_gnl(char *dest, char *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	if (!str2)
		return (1);
	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while ((s1 || s2) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static char	*join_nd_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy_gnl(str, s1, len1);
	ft_memcpy_gnl(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

static char	*extract_line(char **remainder, char *buffer)
{
	char	*line;
	char	*newline_pos;
	char	*new_remainder;

	newline_pos = ft_strchr(*remainder, '\n');
	if (buffer)
		free(buffer);
	if (newline_pos)
	{
		line = malloc((ft_strch(*remainder, '\n') + 2) * sizeof(char));
		ft_memcpy_gnl(line, *remainder, ft_strch(*remainder, '\n') + 1);
		new_remainder = join_nd_free(NULL, newline_pos + 1);
		free(*remainder);
		*remainder = new_remainder;
	}
	else
	{
		line = join_nd_free(NULL, *remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainders;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0)
	{
		free(remainders);
		return (NULL);
	}
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainders = join_nd_free(remainders, buffer);
		if (ft_strchr(remainders, '\n'))
			return (extract_line(&remainders, buffer));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	free(remainders);
	remainders = NULL;
	return (NULL);
}
