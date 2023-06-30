/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:00:38 by victgonz          #+#    #+#             */
/*   Updated: 2023/04/29 01:01:58 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_full_line(int fd, char *spare_line)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	buffer = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (bytes_read != 0 && !get_strchr(spare_line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(spare_line, buffer);
		free(spare_line);
		spare_line = temp;
	}
	free(buffer);
	return (spare_line);
}

static char	*get_line(char *spare_line)
{
	int		i;
	int		len;
	char	*line;

	if (!spare_line[0] || !spare_line)
		return (NULL);
	len = ft_chr_index(spare_line, '\n');
	line = malloc(sizeof(char) * (len + 2));
	if (!spare_line)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		line[i] = spare_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_spare_line(char *spare_line)
{
	int		i;
	int		index;
	char	*newline;

	i = 0;
	if (!spare_line)
		return (NULL);
	index = ft_chr_index(spare_line, '\n');
	if (!spare_line[index])
	{
		free(spare_line);
		return (NULL);
	}
	newline = malloc(sizeof(char) * ft_strlen(spare_line) - index + 1);
	if (!newline)
		return (NULL);
	index++;
	while (spare_line[index])
		newline[i++] = spare_line[index++];
	newline[i] = '\0';
	free(spare_line);
	return (newline);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*spare_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	spare_line = get_full_line(fd, spare_line);
	if (!spare_line)
		return (NULL);
	line = get_line(spare_line);
	spare_line = get_spare_line(spare_line);
	return (line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line1 [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line2 [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line3 [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

*/
