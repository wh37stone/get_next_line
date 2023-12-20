/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:05:06 by joandre-          #+#    #+#             */
/*   Updated: 2023/12/20 02:26:03 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	clean_buffer(char *buffer)
{
	size_t	i;

	i = BUFFER_SIZE + 1;
	while (i--)
		buffer[i] = '\0';
}

bool	is_newline(t_list *node)
{
	size_t	i;

	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i] == '\n')
				return (1);
			i++;
		}
		node = node->next;
	}
	return (0);
}

size_t	get_line_size(t_list *node)
{
	size_t	size;
	size_t	i;

	if (!node)
		return (0);
	size = 0;
	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i] == '\n')
				return (size + 1);
			i++;
			size++;
		}
		node = node->next;
	}
	return (size);
}

void	copy_line(t_list *node, char *line)
{
	size_t	i;
	size_t	j;

	if (!node)
		return ;
	j = 0;
	while (node)
	{
		i = 0;
		while (node->buff[i])
		{
			if (node->buff[i] == '\n')
			{
				line[j] = node->buff[i];
				return ;
			}
			line[j++] = node->buff[i++];
		}
		node = node->next;
	}
}

char	*get_line(t_list *node)
{
	char	*line;

	if (!node)
		return (NULL);
	line = malloc(get_line_size(node) + 1);
	if (!line)
		return (NULL);
	clean_buffer(line);
	copy_line(node, line);
	return (line);
}
