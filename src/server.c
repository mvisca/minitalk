/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/16 01:37:16 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static void	server_handler(int signum, siginfo_t *info, void *ctx);
static int	message_zero(void);
static void	end_handler(int signum);

char	message[1500];

int	main(void)
{
	struct sigaction s_end;
	struct sigaction s_sa;
	
	ft_printf("Server PID <%d>\n", (int)getpid());
	s_end.sa_handler = end_handler;
	s_sa.sa_sigaction = server_handler;
	s_sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_end, NULL);
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1 ||
		sigaction(SIGUSR2, &s_sa, NULL) == -1)
		write (2, "sigaction\n", 10);
	while (1)
		pause();
	return (0);
}

static int	message_zero(void)
{
	int	i;
	
	i = 0;
	while (message[i] || i < 1500)
		i++;
	write (1, &message, i);
	i = 0;
	while (i < 1500)
		message[i++] = 0;
	return (0);
}

static void	server_handler(int signum, siginfo_t *info, void *ctx)
{
	static int				octet = 8;
	static unsigned char	c = 0;
	static int				i = 0;

	(void) ctx;
	ft_printf("PID REMITENTE %d\n", info->si_pid);
	c = c << 1;
	if (signum == SIGUSR1)
		c = c | 1;
	octet--;
	if (octet == 0)
	{
		if (i < 1500)
			message[i++] = c;
		else
			i = message_zero();
		if (c == '\0')
		{
			i = message_zero();
			ft_printf("\n[End of message]\n");
		}
		octet = 8;
		c = 0;
	}
}

static void	end_handler(int signum)
{
	(void)signum;
	ft_printf("\n[CTRL + c] Server terminated\n");
	exit (EXIT_SUCCESS);
}
