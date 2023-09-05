/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:54:35 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/09/05 15:11:03 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minitalk.h>
#include "../include/minitalk.h"

static int	mt_clientatoi(const char *nptr);
static void	mt_send_signal(pid_t pid, char *str1, char *str2);
static void	confirmation_handler(int signum, siginfo_t *info, void *ctx);

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
	mt_send_signal(pid, av[2], av[2]);
	while (1)
	{
		kill(pid, SIGUSR2);
		usleep(2000);
	}
	return (0);
}

static int	mt_clientatoi(const char *nptr)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	return (res);
}

static void	mt_send_signal(pid_t pid, char *str1, char *str2)
{
	int		octet;
	char	c;

	while (*str1)
	{
		octet = 7;
		while (octet >= 0)
		{
			c = *str1;
			c = c >> octet--;
			if (c & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			if ((str1 - str2) % 1000 == 0)
				usleep(2000);
			usleep(100);
		}
		write(1, " (!) [Sending char..", 23);
		if (str1++ && (int)c % 2)
			write(1, "..", 1);
		write(1, "]\n", 2);
	}
	while (++octet < 8 && kill(pid, SIGUSR2))
		usleep(200);
}

static void	confirmation_handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	(void)signum;
	ft_printf("\n (!) [Message reception confirmed]\n");
	ft_printf(" (!) [Terminating program]\n");
	exit (EXIT_SUCCESS);
}
