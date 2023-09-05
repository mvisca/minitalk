/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/09/05 15:04:29 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/include/libft.h"
#include <signal.h>

static void	mt_server_handler(int signum, siginfo_t *info, void *ctx);
static void	mt_print_and_reset_message(unsigned short *i);

char	g_message[1000];

int	main(void)
{
	struct sigaction	s_sa;

	ft_printf("PID: %d\n", (int)getpid());
	s_sa.sa_sigaction = mt_server_handler;
	s_sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1 || \
		sigaction(SIGUSR2, &s_sa, NULL) == -1)
		write (2, "Sigaction\n", 10);
	while (1)
		pause();
	return (0);
}

static void	mt_server_handler(int signum, siginfo_t *info, void *ctx)
{
	static int				octet = 8;
	static unsigned char	c = 0;
	static unsigned short	i = 0;

	(void)ctx;
	c = c << 1;
	if (signum == SIGUSR1)
		c = c | 1;
	octet--;
	if (octet == 0)
	{
		g_message[i++] = c;
		if (c == 0)
		{
			kill(info->si_pid, SIGUSR1);
			mt_print_and_reset_message(&i);
			write (1, "\n (!) [Process complete]\n", 25);
			ft_printf("PID: %d\n", (int)getpid());
		}
		else if (i == 1000)
			mt_print_and_reset_message(&i);
		octet = 8;
		c = 0;
	}
}

static void	mt_print_and_reset_message(unsigned short *i)
{
	write (1, &g_message, *i);
	*i = 0;
	while (*i < 1000)
		g_message[(*i)++] = 0;
	*i = 0;
}
