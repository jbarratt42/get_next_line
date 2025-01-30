/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:15:28 by jbarratt          #+#    #+#             */
/*   Updated: 2025/01/22 12:43:50 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	create_list(t_node **head, int fd)
{
	ssize_t	size;
	ssize_t	size_rest;

	if (!*head)
		return (add_node(head, fd));
	shift_left(*head, seek_nl(*head) + 1);
	size = seek_nl(*head) + 1;
	if (size)
		return (size);
	else
		size = (*head)->size;
	size_rest = add_node(&(*head)->next, fd);
	if (size_rest < 0)
	{
		free(*head);
		*head = NULL;
		return (size_rest);
	}
	return (size + size_rest);
}

/*
size_t	print_node(t_node *n)
{
	char	buf[BUFFER_SIZE + 1];
	strncpy(buf, n->buf, n->size);
	buf[n->size] = 0;
	return(printf("%s", buf));
}
*/

t_node	*consume_list(t_node *head, char *str)
{
	t_node	*tail;
	size_t	i;

	i = 0;
	while (i < head->size && head->buf[i] != '\n')
	{
		str[i] = head->buf[i];
		i++;
	}
	if (!head->next)
	{
		str[i] = '\n';
		return (head);
	}
	tail = consume_list(head->next, str + i);
	free(head);
	return (tail);
}

char	*get_next_line(int fd)
{
	static t_node	*head[MAX_OPEN_FILES + 3];
	ssize_t			size;
	char			*str;

	if (head[fd] && !head[fd]->size)
	{
		free_node(&head[fd]);
		return (NULL);
	}
	size = create_list(&head[fd], fd);
	if (size == 0)
		free_node(&head[fd]);
	if (size <= 0)
		return (NULL);
	str = malloc(size + 1);
	if (!str)
	{
		free_node(&head[fd]);
		return (NULL);
	}
	head[fd] = consume_list(head[fd], str);
	str[size] = '\0';
	return (str);
}
