/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:41:16 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/09 13:04:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putstr(va_list params, int *i)
{
	int		control;
	char	*value;

	value = va_arg(params, char *);
	if (value)
		control = write (1, value, ft_strlen(value));
	else
		control = write(1, "(null)", 6);
	(*i)++;
	return (control);
}
