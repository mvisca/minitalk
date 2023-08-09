/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:36:51 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/09 13:03:32 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_lstsize(t_list *lst)
{
	int		ncount;

	ncount = 0;
	while (lst)
	{
		lst = lst->next;
		ncount++;
	}
	return (ncount);
}
