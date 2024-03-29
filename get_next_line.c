/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2024/02/15 03:13:36 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static t_list	*free_node(t_list **node, t_list *new, char *buffer)
{
	t_list	*linx;

	if (!node || !new || !buffer)
		return (NULL);
	while (*node)
	{
		linx = (*node)->next;
		free((*node)->buff);
		free(*node);
		*node = linx;
	}
	if (new->buff[0])
		*node = new;
	else
	{
		free(buffer);
		free(new);
		return (NULL);
	}
	return (new);
}

static t_list	*clear_list(t_list **node)
{
	t_list	*last;
	t_list	*new;
	char	*buffer;
	size_t	i;
	size_t	j;

	if (!(*node))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (!buffer || !new)
		return (NULL);
	clean_buffer(buffer, BUFFER_SIZE + 1);
	last = last_node(*node);
	i = 0;
	while (last->buff[i] && last->buff[i] != '\n')
		i++;
	j = 0;
	if (last->buff[i])
		while (last->buff[++i])
			buffer[j++] = last->buff[i];
	new->buff = buffer;
	new->next = NULL;
	return (free_node(node, new, buffer));
}

static void	create_list(t_list **node, int fd)
{
	char	*buffer;
	t_list	*new;

	while (!is_newline(*node))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		clean_buffer(buffer, BUFFER_SIZE + 1);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			free(buffer);
			return ;
		}
		new = malloc(sizeof(t_list));
		if (!new)
			return ;
		if (!(last_node(*node)))
			*node = new;
		else
			(last_node(*node))->next = new;
		new->buff = buffer;
		new->next = NULL;
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&node, fd);
	if (!node)
		return (NULL);
	line = malloc(get_line_size(node) + 1);
	if (!line)
		return (NULL);
	clean_buffer(line, get_line_size(node) + 1);
	copy_line(node, line);
	node = clear_list(&node);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	char	*line;
	int	fd;
	size_t	n;

	n = 1;
	fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("[LINE %zu] %s", n++, line);
		free (line);
	}
	close(fd);
	return (0);
}*/
