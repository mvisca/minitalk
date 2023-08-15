/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/15 11:42:28 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	server_handler(int signum);
static void	end_handler(int signum);

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

static void	server_handler(int signum)
{
	static int				octet = 8;
	static unsigned char	c = 0;

	c = c << 1;
	if (signum == SIGUSR1)
		c = c | 1;
	octet--;
	ft_printf("bit %d\n", c & 1);
	if (!octet)
	{
		if (c == '\0')
			ft_printf("END\n");
		ft_printf("c = %c\n", c);
		octet = 8;
		c = 0;
	}
}

static void	end_handler(int signum)
{
	(void)signum;
	ft_printf("Server terminated\n");
	exit (EXIT_SUCCESS);
}
