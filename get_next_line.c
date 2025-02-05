/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpicchio <gpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:56:53 by gpicchio          #+#    #+#             */
/*   Updated: 2024/11/21 17:50:59 by gpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean(char *line)
{
	char	*rest;
	int		i;

	if (*line == '\0')
		return (free(line), NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	rest = ft_strdup(line + i);
	if (!rest)
		return (NULL);
	free(line);
	return (rest);
}

char	*get_first_line(char *line)
{
	ssize_t	i;
	char	*first_line;

	if (!line || *line == '\0')
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		i++;
	}
	first_line = (char *)malloc(i + 2);
	if (!first_line)
		return (NULL);
	ft_strlcpy(first_line, line, i + 2);
	return (first_line);
}

char	*append(int fd, char *line)
{
	ssize_t			rd;
	char			*buffer;
	char			*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(line, '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[rd] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;

	if (fd == -42)
		return (free(line), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	line = append(fd, line);
	if (!line)
		return (NULL);
	ret = get_first_line(line);
	line = clean(line);
	return (ret);
}
/* 
int main(int ac, char **av)
{
	int fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	(void)ac;
	return (0);
} */
