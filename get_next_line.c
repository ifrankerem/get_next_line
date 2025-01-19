/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarslan <iarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:58:37 by iarslan           #+#    #+#             */
/*   Updated: 2025/01/19 03:05:59 by iarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_free(char *buf, char *readed_line)
{
	char	*temp;

	temp = ft_strjoin(buf, readed_line);
	free(buf);
	return (temp);
}

char	*ft_next(char *buf)
{
	char	*new_remainder;
	char	*newline_pos;

	newline_pos = ft_strchr(buf, '\n');
	if (!newline_pos)
	{
		free(buf);
		return (NULL);
	}
	new_remainder = ft_strdup(newline_pos + 1);
	free(buf);
	return (new_remainder);
}

char	*ft_extract_line(char *buf)
{
	char	*line;
	int		copy_length;

	if (!buf || !*buf)
		return (NULL);
	copy_length = 0;
	while (buf[copy_length] && buf[copy_length] != '\n')
		copy_length++;
	if (buf[copy_length] == '\n')
		copy_length++;
	line = ft_calloc(copy_length + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, buf, copy_length);
	return (line);
}

char	*ft_read(int fd, char *buf)
{
	int		chars_read;
	char	*readed_line;

	if (!buf)
		buf = ft_calloc(1, 1);
	readed_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!readed_line || !buf)
		return (free(readed_line), free(buf), NULL);
	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, readed_line, BUFFER_SIZE);
		if (chars_read < 0)
			break ;
		readed_line[chars_read] = '\0';
		buf = ft_free(buf, readed_line);
		if (!buf || ft_strchr(buf, '\n'))
			break ;
	}
	free(readed_line);
	if (chars_read < 0)
		return (free(buf), NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_read(fd, buf);
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
