/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai <tlai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:58:41 by tlai              #+#    #+#             */
/*   Updated: 2023/11/25 17:23:30 by tlai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*get_remains(char *basin_buffer);
char	*extract_line(char *basin_buffer);
char	*attach_buffer(char *basin_buffer, char *cup_buffer);
char	*read_from_file(char *basin_buffer, int fd);

#endif