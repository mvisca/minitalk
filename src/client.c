/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/14 13:20:01 by mvisca           ###   ########.fr       */
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
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		str++;
	}	
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
		return (1);
	pid = mt_clientatoi(av[1]);
	mt_send_signal(pid, av[2]);
	mt_send_signal(pid, 0);
	return (0);
}
