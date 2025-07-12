/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakawamo <hakawamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:52:28 by hakawamo          #+#    #+#             */
/*   Updated: 2024/12/06 21:51:35 by hakawamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	size_t	capacity;
	size_t	length;
	int		result;

	line = NULL;
	capacity = 16;
	length = 0;
	line = (char *)malloc(capacity);
	if (!line)
		return (NULL);
	result = process_characters(fd, &line, &capacity, &length);
	if (result <= 0)
	{
		free(line);
		return (NULL);
	}
	line[length] = '\0';
	return (line);
}

// int main(void) {
//     int fd = open("example.txt", O_RDONLY);
//     if (fd < 0) 
//         return (-1);

//     char *line;
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s", line);
//         free(line);
//     }

//     close(fd);
//     return (0);
// }
