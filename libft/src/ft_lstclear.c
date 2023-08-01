/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:33:49 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/20 20:45:57 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*current_node;

	current_node = *lst;
	while (current_node)
	{
		next_node = current_node->next;
		del(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}
