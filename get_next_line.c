/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atito <atito@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:29:41 by atito             #+#    #+#             */
/*   Updated: 2022/11/03 12:05:41 by atito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

static char	*free_null(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

static char	*get_buff(char *buff, int fd)
{
	int		byte;
	char	*input;
	char	*tmp;

	input = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!input)
		return (NULL);
	byte = 1;
	while (byte && !ft_strchr(buff, '\n'))
	{
		byte = read(fd, input, BUFFER_SIZE);
		if (byte == -1)
			return (free_null(input));
		if (!byte)
			break ;
		input[byte] = '\0';
		tmp = ft_strjoin(buff, input);
		if (!tmp)
			return (free_null(input));
		free_null(buff);
		buff = tmp;
	}
	free_null(input);
	return (buff);
}

static char	*add_line(char *buff, char *line)
{
	size_t	cnt;
	char	*trim;
	char	*tmp;

	cnt = 0;
	if (!buff)
		return (NULL);
	while (buff[cnt] && buff[cnt] != '\n')
		cnt += 1;
	if (buff[cnt] == '\n')
		cnt += 1;
	trim = ft_substr(buff, 0, cnt);
	if (!trim)
		return (free_null(buff));
	tmp = ft_strjoin(line, trim);
	free_null(line);
	line = tmp;
	free_null(trim);
	if (!line)
		return (NULL);
	if (!ft_strlen(line))
		return (free_null(line));
	return (line);
}

static char	*save_buff(char *buff)
{
	size_t	cnt;
	char	*tmp;

	cnt = 0;
	if (!buff)
		return (NULL);
	if (!ft_strlen(buff))
		return (free_null(buff));
	while (buff[cnt] != '\n' && buff[cnt] != '\0')
		cnt += 1;
	if (buff[cnt] == '\n')
		cnt += 1;
	tmp = ft_substr(buff, cnt, ft_strlen(buff) - cnt);
	free_null(buff);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(buff, '\n'))
		buff = get_buff(buff, fd);
	line = add_line(buff, line);
	buff = save_buff(buff);
	return (line);
}
