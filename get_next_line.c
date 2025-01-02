/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarslan <iarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:58:37 by iarslan           #+#    #+#             */
/*   Updated: 2025/01/03 01:31:31 by iarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next(char *remainder)
{
	char	*new_remainder;
	char	*newline_pos;

	if (!remainder)
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (!newline_pos)
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_strdup(newline_pos + 1);
	free(remainder);
	return (new_remainder);
}

char	*ft_extract_line(char *remainder)
{
	char	*line;
	int		i;
	int		copy_length;

	i = 0;
	if (!remainder || !*remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	copy_length = i;
	if (remainder[i] == '\n')
		copy_length++;
	line = ft_calloc(copy_length + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, remainder, copy_length);
	return (line);
}

char	*ft_read(int fd, char *remainder)
{
	int		chars_read;
	char	*readed_line;

	if (!remainder)
		remainder = ft_calloc(1, 1);
	readed_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!readed_line || !remainder)
		return (free(readed_line), free(remainder), NULL);
	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, readed_line, BUFFER_SIZE);
		if (chars_read < 0)
			break ;
		readed_line[chars_read] = '\0';
		remainder = ft_free(remainder, readed_line);
		if (!remainder || ft_strchr(remainder, '\n'))
			break ;
	}
	free(readed_line);
	if (chars_read < 0)
		return (free(remainder), NULL);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		return (NULL);
	}
	buf = ft_read(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_extract_line(buf);
	if (!line)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	buf = ft_next(buf);
	return (line);
}
