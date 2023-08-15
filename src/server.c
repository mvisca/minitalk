/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/15 15:08:02 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	server_handler(int signum);
static int	message_zero(void);
static void	end_handler(int signum);

char	message[1500];

int	main(void)
{
	ft_printf("Server -> process ID <%d>\n", (int)getpid());
	signal(SIGUSR1, server_handler);
	signal(SIGUSR2, server_handler);
	signal(SIGINT, end_handler);
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

static void	server_handler(int signum)
{
	static int				octet = 8;
	static unsigned char	c = 0;
	static int				i = 0;

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
