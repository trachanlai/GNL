/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai <tlai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:19:25 by tlai              #+#    #+#             */
/*   Updated: 2023/11/24 20:21:46 by tlai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char*s2)
{
	char		*str_joined;
	size_t		i;
	size_t		j;

	str_joined = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if ((s1 == NULL || s2 == NULL || str_joined == NULL))
		return (NULL);
	while (s1[i])
	{
		str_joined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str_joined[i + j] = s2[j];
		j++;
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' || *s == (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_size;
	void			*allocated_memory;
	unsigned char	*a;

	total_size = count * size;
	allocated_memory = malloc(total_size);
	a = (unsigned char *)allocated_memory;
	if (allocated_memory != NULL)
	{
		while (total_size > 0)
		{
			*a = 0;
			a++;
			total_size--;
		}
	}
	else
		return (NULL);
	return (allocated_memory);
}
