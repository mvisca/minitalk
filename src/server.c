/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/14 13:30:19 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <minitalk.h>
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
	static t_mssg	mssg = {8, 0};
	
	mssg.character |= (signum == SIGUSR1);
	mssg.current_bit--;
	mssg.character <<= 1;
	if (mssg.current_bit <= 0)
	{
		ft_printf("curr bit = %c\n", mssg.character);
		mssg.current_bit = 8;
		if (mssg.character == '\0')
		{
			ft_printf("\nEND\n");
		}
	}
}

static void	end_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("Clear\n");
	exit (EXIT_SUCCESS);
}
