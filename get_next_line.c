/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <rlevilla@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:59:42 by rlevilla          #+#    #+#             */
/*   Updated: 2022/12/09 20:23:18 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
# define BUFFER_SIZE 42

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
	char	buf[BUFFER_SIZE + 1];

	bytes_read = 1;
	if (!temp)
		temp = gnl_calloc(1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp = gnl_strjoin(temp, buf);
		if (check_c(temp) != -1)
			break ;
	}
	return (temp);
}
*/
char	*gnl_extract_line(char *temp)
{
	ssize_t	i;
	char	*str;

	i = 0;
	if (temp[0] == '\0')
		return (NULL);
	while (temp[i])
	{
		if (temp[i++] == '\n')
			break ;
		i++;
	}
	str = gnl_calloc(i + 1);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			str[i] = temp[i];
			return (str);
		}
		str[i] = temp[i];
		i++;
	}
	return (str);
}

char	*gnl_strndup(char *temp)
{
	ssize_t	i;
	ssize_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	str = gnl_calloc(i + 1);
	i = 0;
	while (temp[i])
	{
		str[j++] = temp[i++];
	}
	return (str);
}

char	*gnl_strchr(char *temp)
{
	ssize_t	i;
	char	*res;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			res = gnl_strndup(&temp[++i]);
			free(temp);
			return (res);
		}
		i++;
	}
	free(temp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*gnl;
	static char	*temp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	//if (!temp || check_c(temp) == -1)
	temp = search_line(fd, temp);
	if (temp == NULL)
	{
		free(temp);
		return (NULL);
	}
	gnl = gnl_extract_line(temp);
	temp = gnl_strchr(temp);
	return (gnl);
}

int main(void)
{
	int fd;
	char	*line;

	fd = open("43_no_nl.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("HORS BOUCLE =%s", get_next_line(fd));
	printf("HORS BOUCLE =%s", get_next_line(fd));
	printf("HORS BOUCLE =%s", get_next_line(fd));
	close(fd);
	return (0);
}

/*
int main(void)
{
	int fd;
	//int	i;

	fd = open("41_with_nl.txt", O_RDONLY);
	//i = 0;
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
*/
/*
int main(void)
{
	int fd;

	fd = open("gnl2.txt", O_RDONLY);
	printf("GET_NEXT_LINE =%s", get_next_line(fd));
	printf("GET_NEXT_LINE =%s", get_next_line(fd));
	printf("GET_NEXT_LINE =%s", get_next_line(fd));
	printf("GET_NEXT_LINE =%s", get_next_line(fd));
	return (0);
}*/
