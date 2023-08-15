/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.xc                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:18:45 by mvisca            #+#    #+#             */
/*   Updated: 2023/08/15 17:31:51 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
//#include <minitalk.h>

t_char_node *mt_chrlst_new(t_char_node **head, char c)
{
	t_char_node *node;

	node = (t_char_node *) malloc (sizeof(t_char_node));
	if (!node)
	{
		mt_chrlst_clear(head);
		return (NULL);
	}
	node->character = c;
	node->next = NULL;
	return (node);
}

void	mt_chrlst_add(t_char_node **head, t_char_node *new)
{
	t_char_node	*aux;

	if (!*head)
	{
		*head = new;
		return ;
	}
	aux = *head;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

void mt_chrlst_clear(t_char_node **head)
{
	t_char_node	*aux;
	t_char_node	*next;

	aux = head;
	while (aux)
	{
		next = aux->next;
		free(aux);
		aux = next;
	}
	free(head);
}

void	mt_print_list(t_char_node *head)
{
	char	c;

	while (head)
	{
		c = head->character;
		write (1, &c, 1);
		head = head->next;
		ft_printf("\naqui\n");
	}
	mt_chrlst_clear(head);
}
