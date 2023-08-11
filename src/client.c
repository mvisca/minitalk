/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/11 00:46:35 by mvisca           ###   ########.fr       */
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

static void	mt_send_signal(pid_t pid, char c)
{
	int	bit;
	int	i;

	bit = 0;
	i = 7;
	while (i >= 0)
	{
		bit = c >> i & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	char		*str;
	pid_t		pid;

	if (ac != 3)
		return (1);
	str = av[2];
	pid = mt_clientatoi(av[1]);
	while (*str)
	{
		mt_send_signal(pid, *str);
		str++;
	}
	return (0);
}
