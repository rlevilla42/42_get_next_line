/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <rlevilla@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:00:39 by rlevilla          #+#    #+#             */
/*   Updated: 2022/12/06 17:34:42 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

ssize_t	check_c(char *temp)
{
	ssize_t	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_calloc(ssize_t buf_size)
{
	ssize_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * buf_size);
	while (i < buf_size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*gnl_strjoin(char *temp, char *buf)
{
	ssize_t	i;
	ssize_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = gnl_calloc(ft_strlen(temp) + ft_strlen(buf) + 1);
	while (temp[i])
	{
		str[i] = temp[i];
		i++;
	}
	while (buf[j])
		str[i++] = buf[j++];
	free(temp);
	return (str);
}

char	*search_line(int fd, char *temp)
{
	ssize_t	bytes_read;
	char	*buf;

	bytes_read = 1;
	if (!temp)
		temp = gnl_calloc(1);
	buf = gnl_calloc(BUFFER_SIZE + 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			free(temp);
			return (NULL);
		}
		temp = gnl_strjoin(temp, buf);
		if (check_c(temp) != -1)
			break ;
	}
	free(buf);
	return (temp);
}
