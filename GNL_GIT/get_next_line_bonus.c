/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai <tlai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:01:08 by tlai              #+#    #+#             */
/*   Updated: 2023/11/25 17:29:32 by tlai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// return value:
// Read line: correct behavior
// NULL: there is nothing else to read, or an error
// Write a function that returns a line read from a
// file descriptor

char	*get_remains(char *basin_buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	if (!basin_buffer[i])
	{
		free (basin_buffer);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(basin_buffer) - i + 1, sizeof(char));
	i++;
	while (basin_buffer[i] != '\0')
	{
		line[j] = basin_buffer[i];
		j++;
		i++;
	}
	free (basin_buffer);
	return (line);
}

char	*extract_line(char *basin_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!basin_buffer[i])
		return (NULL);
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
	{
		line[i] = basin_buffer[i];
		i++;
	}
	if (basin_buffer[i] && basin_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*attach_buffer(char *basin_buffer, char *cup_buffer)
{
	char	*temp_buffer;

	temp_buffer = ft_strjoin(basin_buffer, cup_buffer);
	free (basin_buffer);
	return (temp_buffer);
}

// Read data from file and append it to partial content

char	*read_from_file(char *basin_buffer, int fd)
{
	ssize_t		bytes_read;
	char		cup_buffer[BUFFER_SIZE + 1];

	if (!basin_buffer)
		basin_buffer = ft_calloc(1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (basin_buffer);
			return (NULL);
		}
		cup_buffer[bytes_read] = 0;
		basin_buffer = attach_buffer(basin_buffer, cup_buffer);
		if (!basin_buffer)
			return (NULL);
		if (ft_strchr(cup_buffer, '\n'))
			break ;
	}
	return (basin_buffer);
}

// - basin_buffer is a persistent buffer to store partial content read
// from the fd every time and lives until the end of the program. 
// Hence declared static.
// - It retains its value between successive calls to get_next_line.

char	*get_next_line(int fd)
{
	static char	*basin_buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	basin_buffer[fd] = read_from_file(basin_buffer[fd], fd);
	if (basin_buffer[fd] == NULL)
		return (NULL);
	line = extract_line(basin_buffer[fd]);
	basin_buffer[fd] = get_remains(basin_buffer[fd]);
	return (line);
}

// #include <stdio.h>
// int main ()
// {
// 	int		fd;
// 	int		fd2;
// 	char	*next_line;

// 	fd = open("text.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	next_line = get_next_line(fd);
// 	printf("string: %s", next_line);

// 	// printf("next line: %s \n fd: %d \n", next_line, fd);
// 	while (next_line != NULL)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("string: %s", next_line);
// 		next_line = get_next_line(fd2);
// 		printf("string: %s", next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	close(fd2);
// 	return (0);
// }
