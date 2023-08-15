/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/15 13:42:12 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minitalk.h>
#include "../include/minitalk.h"

static int	mt_clientatoi(const char *nptr)
{
	unsigned int	res;
	int				i;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	return (res);
}

static void	mt_send_signal(pid_t pid, char *str)
{
	int		octet;
	int		bit;
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		octet = 7;
		while (octet >= 0)
		{
			c = str[i];
			c = c >> octet--;
			bit = c & 1;
			ft_printf("bit %d\n", bit);
			if (bit == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		i++;
		ft_printf("%c %d\n", c, (int)c);
	}
	octet = 8;
	while (octet > 0)
	{
		ft_printf("bit %d\n", 0);
		kill(pid, SIGUSR2);
		usleep(100);
		octet--;
	}
	ft_printf("\'\\n\'");
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
		return (1);
	pid = mt_clientatoi(av[1]);
	mt_send_signal(pid, av[2]);
	return (0);
}
