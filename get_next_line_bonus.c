/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2024/02/16 15:43:35 by joandre-         ###   ########.fr       */
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

	while (!is_newline(node[fd]))
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
		if (!(last_node(node[fd])))
			node[fd] = new;
		else
			(last_node(node[fd]))->next = new;
		new->buff = buffer;
		new->next = NULL;
	}
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*node[4242];

	if (fd < 0 || fd > 4241 ||  BUFFER_SIZE <= 0)
		return (NULL);
	create_list(node, fd);
	if (!node[fd])
		return (NULL);
	line = malloc(get_line_size(node[fd]) + 1);
	if (!line)
		return (NULL);
	clean_buffer(line, get_line_size(node[fd]) + 1);
	copy_line(node[fd], line);
	node[fd] = clear_list(&node[fd]);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	char	*line[5];
	int		fd[5];
	size_t	n[5] = {1, 1, 1, 1, 1};
	bool	nils[5] = {0, 0, 0, 0, 0};
	size_t	o = 0;
	size_t	i = 0;
	size_t	j = 0;

	fd[0] = open("gnlTester/files/big_line_no_nl", O_RDONLY);
	fd[1] = open("gnlTester/files/alternate_line_nl_with_nl", O_RDONLY);
	fd[2] = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
	fd[3] = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	fd[4] = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
	while (true)
	{
		if ((line[i] = get_next_line(fd[i])))
		{
			printf("\n[FILE %zu]\t[LINE %zu]\n%s", i, n[i]++, line[i]);
			free (line[i]);
			line[i] = NULL;
		}
		else if (!line[i])
			nils[i] = true;
		j = 0;
		while (j < 5)
		{
			if (nils[j])
				o++;
			else
				o = 0;
			j++;
		}
		if (++i == 5)
			i = 0;
		if (o > 4)
			break ;
	}
	i = 0;
	while (i < 5)
		close(fd[i++]);
	return (0);
}*/
