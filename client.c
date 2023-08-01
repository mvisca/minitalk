/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/26 17:04:17 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_clientatoi(const char *nptr)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	return (res);
}

int	main(int ac, char **av)
{
	char	*str;
	int		bit;
	int		c;
	int		i;

	if (ac != 3)
		return (1);
	str = av[2];
	while (*str)
	{
		bit = 0;
		c = *(str++);
		i = 7;
		while (i >= 0)
		{
			bit = c >> i-- & 1;
			if (bit == 1)
				kill(ft_clientatoi(av[1]), SIGUSR1);
			else
				kill(ft_clientatoi(av[1]), SIGUSR2);
			usleep(100);
		}
	}
	return (0);
}
