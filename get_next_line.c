/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:29:46 by joandre-          #+#    #+#             */
/*   Updated: 2023/12/20 02:58:52 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static t_list	*last_node(t_list *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

static t_list	*free_node(t_list **node, t_list *new_node, char *buffer)
{
	t_list	*linx;

	while (*node)
	{
		linx = (*node)->next;
		free((*node)->buff);
		free(*node);
		*node = linx;
	}
	*node = NULL;
	if (new_node->buff[0])
		*node = new_node;
	else
	{
		free(buffer);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

static t_list	*clear_list(t_list **node)
{
	t_list	*new;
	char	*buffer;
	size_t	i;
	size_t	j;

	buffer = malloc(BUFFER_SIZE + 1);
	new = malloc(sizeof(t_list));
	if (!buffer || !new)
		return (NULL);
	clean_buffer(buffer);
	*node = last_node((*node));
	i = 0;
	while ((*node)->buff[i] && (*node)->buff[i] != '\n')
		i++;
	j = 0;
	while ((*node)->buff[i] && (*node)->buff[++i] != '\n')
		buffer[j++] = (*node)->buff[i];
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
		clean_buffer(buffer);
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
	line = get_line(node);
	node = clear_list(&node);
	return (line);
}
