/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarratt <jbarratt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:25:46 by jbarratt          #+#    #+#             */
/*   Updated: 2025/01/22 11:48:25 by jbarratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define MALLOC_ERROR -2
# define READ_ERROR -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_node	t_node;
typedef struct s_node
{
	char	buf[BUFFER_SIZE];
	size_t	size;
	t_node	*next;
}			t_node;
char	*get_next_line(int fd);
ssize_t	seek_nl(t_node *n);
ssize_t	file_to_node(t_node **n, int fd);
ssize_t	add_node(t_node **n, int fd);
void	shift_left(t_node *n, size_t width);
ssize_t	create_list(t_node **head, int fd);
t_node	*consume_list(t_node *head, char *str);
void	free_node(t_node **n);
//size_t	print_node(t_node *n);
#endif
