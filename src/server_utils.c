/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:18:45 by mvisca            #+#    #+#             */
/*   Updated: 2023/08/10 16:04:16 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
//#include <minitalk.h>

t_char_node *mt_chrlst_new(t_char_node *head, char c)
{
	t_char_node *node;

	node = (t_char_node *) malloc (sizeof(t_char_node));
	if (!node)
	{
		mt_chrlst_clear(head);
		exit (EXIT_FAILURE);
	}
	node->character = c;
	node->next = NULL;
	return (node);
}

t_char_node	*mt_chrlst_add(t_char_node **head, t_char_node *new)
{
	t_char_node	*aux;

	ft_printf("add %c\n", new->character);
	if (!*head)
	{
		*head = new;
		return (*head);
	}
	aux = *head;
	while (aux->next)
	{
		ft_printf("add loop for char %c\n", new->character);
		aux = aux->next;
	}
	aux->next = new;
	return (*head);
}

void mt_chrlst_clear(t_char_node *head)
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
}

void	mt_print_list(t_char_node *head)
{
	char		*str;
	char		*new;
	t_char_node	*aux;

	ft_printf("print\n");
	if (!head)
		return ;
	str = ft_strdup("");
	aux = head;
	while (aux)
	{
		new = ft_strjoin(str, (char *)&aux->character);
		free(str);
		str = new;
		aux = aux->next;
	}
	ft_printf("%s\n", str);
	ft_printf("fin\n");
	free(str);
}
