/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakawamo <hakawamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:52:24 by hakawamo          #+#    #+#             */
/*   Updated: 2024/11/29 21:32:35 by hakawamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == 0)
			return (EOF);
		if (n < 0)
			return (-2);
		bufp = buf;
	}
	if (--n >= 0)
		return ((unsigned char)*bufp++);
	else
		return (EOF);
}

char	*expand_buffer(char *line, size_t *capacity, size_t length)
{
	size_t	new_capacity;
	char	*new_line;
	size_t	i;

	new_capacity = (*capacity) * 2;
	new_line = (char *)malloc(new_capacity);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	*capacity = new_capacity;
	return (new_line);
}

int	process_characters(int fd, char **line, size_t *capacity, size_t *length)
{
	char	c;

	while (1)
	{
		c = ft_getc(fd);
		if (c == -2)
			return (-1);
		if (c == EOF)
		{
			if (*length == 0)
				return (0);
			break ;
		}
		if (*length + 1 >= *capacity)
		{
			*line = expand_buffer(*line, capacity, *length);
			if (!*line)
				return (-1);
		}
		(*line)[(*length)++] = c;
		if (c == '\n')
			break ;
	}
	return (1);
}
