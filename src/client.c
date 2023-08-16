/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/16 12:44:44 by mvisca           ###   ########.fr       */
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
			if (bit == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(400);
			if (i % 1500 == 0)
				usleep(8000);
		}
		write (1, "sending... ", 11);
		write (1, &str[i], 1);
		write (1, "\n", 1);
		i++;
	}
	octet = 8;
	while (octet > 0)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		octet--;
	}
}

static void	confirmation_handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	(void)signum;
	ft_printf(" [Message reception confirmed]\n");
	ft_printf(" [Terminating program]\n");
	exit (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	s_sa;

	if (ac != 3)
		return (1);
	pid = mt_clientatoi(av[1]);
	s_sa.sa_sigaction = confirmation_handler;
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1)
		write (2, "sigaction\n", 10);
	mt_send_signal(pid, av[2]);
	while (1)
		pause();
	return (0);
}
