/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <rlevilla@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:59:42 by rlevilla          #+#    #+#             */
/*   Updated: 2022/12/06 23:22:22 by rlevilla         ###   ########.fr       */
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
		if (bytes_read == 0)
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

char	*gnl_extract_line(char *temp)
{
	ssize_t	i;
	char	*str;

	i = 0;
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

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\n')
		{
			return (gnl_strndup(&temp[++i]));
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*gnl;
	static char	*temp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
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
	int	fd;

	fd = open("41_no_nl.txt", O_RDONLY);
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
}
/*
int main(void)
{
	int fd;
	//int	i;

	fd = open("gnl.txt", O_RDONLY);
	//i = 0;
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
	printf("GET NEXT LINE =%s", get_next_line(fd));
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
