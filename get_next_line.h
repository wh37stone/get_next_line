/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:38:32 by joandre-          #+#    #+#             */
/*   Updated: 2023/12/20 03:03:01 by joandre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list
{
	char			*buff;
	struct s_list	*next;
}	t_list;
void	clean_buffer(char	*buffer);
bool	is_newline(t_list *node);
size_t	get_line_size(t_list *node);
void	copy_line(t_list *node, char *line);
char	*get_line(t_list *node);
char	*get_next_line(int fd);

#endif
