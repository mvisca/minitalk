/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/01 19:45:41 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_signals	g_signals = {7, NULL, 0};

static t_chrlst	*new_chrlst(char c)
{
	t_chrlst	*new;

	new = (void *) malloc (sizeof(t_chrlst));
	if (new)
	{
		new->character = c;
		new->next = NULL;
	}
	return (new);
}

static void	clear_chrlst(t_chrlst *head)
{
	t_chrlst	*aux;

	aux = head;
	free(content);
	content = NULL;
}

static void	print_list(t_chrlst **head)
{
	if (!head || !(*head)->character)
		return ;
	while (head)
	{
		ft_printf("%c", (*head)->character);
		head = (*head)->next;
	}
}

static void	server_handler(int signum)
{
	t_chrlst	*new;

	if (signum == SIGUSR1)
		g_signals.character = 1 << g_signals.current_bit | g_signals.character;
	if (g_signals.current_bit == 0)
	{
		new = new_chrlst(g_signals.character);
		if (!new)
		{
			clear_chrlst(&(g_signals.head));
			exit (1);
		}
		ft_lstadd_back(g_signals.head, new);
		g_signals.character = 0;
		g_signals.current_bit = 7;
	}
	else
		g_signals.current_bit--;
	if (g_signals.character == '\0')
	{
		print_list(g_signals.head);
	}
}

int	main(void)
{
	ft_printf("%d\n", (int)getpid());
	signal(SIGUSR1, server_handler);
	signal(SIGUSR2, server_handler);
	while (1)
		pause();
	return (0);
}
