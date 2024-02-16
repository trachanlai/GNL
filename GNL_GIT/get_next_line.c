/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai <tlai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:27:27 by tlai              #+#    #+#             */
/*   Updated: 2023/12/05 18:07:32 by tlai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	if (!basin_buffer[i])
	{
		free (basin_buffer);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(basin_buffer) - i + 1, sizeof(char));
	i++;
	j = 0;
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
	if (basin_buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
	{
		line[i] = basin_buffer[i];
		i++;
	}
	if (basin_buffer[i] == '\n')
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
		if (basin_buffer == NULL)
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
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	basin_buffer = read_from_file(basin_buffer, fd);
	if (basin_buffer == NULL)
		return (NULL);
	line = extract_line(basin_buffer);
	basin_buffer = get_remains(basin_buffer);
	return (line);
}

#include <stdio.h>
int main ()
{
	int		fd;
	char	*next_line;

	fd = open("text.txt", O_RDONLY);
	// if (fd == -1)
	// {
	// 	printf("Error opening file");
	// 	return (1);
	// }
	next_line = get_next_line(fd);
	// // next_line = get_next_line(fd);
	// printf("string: %s", next_line);
	// next_line = get_next_line(fd);
	// // next_line = get_next_line(fd);
	// printf("string2: %s", next_line);
	while (next_line != NULL)
	{
		next_line = get_next_line(fd);
		printf("string: %s", next_line);
		free(next_line);
	}
	close(fd);
	return (0);
}
