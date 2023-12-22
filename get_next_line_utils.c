/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:05:06 by joandre-          #+#    #+#             */
/*   Updated: 2023/12/21 23:31:31 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	clean_buffer(char *buffer, size_t len)
{
	if (!buffer || len == 0)
		return ;
	while (len--)
		buffer[len] = '\0';
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

	if (!node || !line)
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
