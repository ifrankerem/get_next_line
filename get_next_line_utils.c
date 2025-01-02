/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarslan <iarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:58:39 by iarslan           #+#    #+#             */
/*   Updated: 2025/01/03 01:33:14 by iarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*x;
	size_t			i;
	unsigned char	*str;

	x = malloc(count * size);
	if (!x)
		return (NULL);
	str = (unsigned char *)x;
	i = 0;
	while (i < (count * size))
	{
		str[i] = '\0';
		i++;
	}
	return (x);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	int		i;
	int		j;
	int		s1size;
	int		s2size;

	i = 0;
	j = 0;
	s1size = 0;
	s2size = 0;
	while (s1[s1size])
		s1size++;
	while (s2[s2size])
		s2size++;
	final = malloc(sizeof(char) * (s1size + s2size + 1));
	if (!final)
		return (NULL);
	while (s1[i])
		final[j++] = s1[i++];
	i = 0;
	while (s2[i])
		final[j++] = s2[i++];
	final[j] = '\0';
	return (final);
}

char	*ft_strdup(const char *s1)
{
	char	*final;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	final = malloc(sizeof(char) * (len + 1));
	if (!final)
		return (NULL);
	while (s1[i])
	{
		final[i] = s1[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*source;
	unsigned char		*destination;

	i = 0;
	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
