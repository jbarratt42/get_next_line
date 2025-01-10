/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:17:55 by jbarratt          #+#    #+#             */
/*   Updated: 2025/01/10 14:37:16 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	seek_nl(t_node *n)
{
	size_t	i;

	i = 0;
	while (i < n->size && n->buf[i] != '\n')
		i++;
	if (i == n->size)
		return (-1);
	return (i);
}

ssize_t	file_to_node(t_node **n, int fd)
{
	ssize_t	size;

	*n = malloc(sizeof(t_node));
	if (!*n)
		return (MALLOC_ERROR);
	size = read(fd, (*n)->buf, BUFFER_SIZE);
	if (size < 0)
	{
		free(*n);
		return (READ_ERROR);
	}
	(*n)->next = NULL;
	(*n)->size = size;
	return (size);
}

ssize_t	add_node(t_node **n, int fd)
{
	ssize_t	pos_nl;
	ssize_t	size;
	ssize_t	size_rest;

	size = file_to_node(n, fd);
	if (size <= 0)
		return (size);
	pos_nl = seek_nl(*n);
	if (pos_nl >= 0)
		return (pos_nl + 1);
	size_rest = add_node(&(*n)->next, fd);
	if (size_rest < 0)
		return (size_rest);
	return ((*n)->size + size_rest);
}

void	shift_left(t_node *n, size_t width)
{
	size_t	i;
	size_t	j;

	i = width;
	j = 0;
	while (i < n->size)
		n->buf[j++] = n->buf[i++];
	n->size -= width;
}
