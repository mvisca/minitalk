/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:03:44 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/17 00:43:01 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/include/libft.h"
#include <signal.h>

static void	server_handler(int signum, siginfo_t *info, void *ctx);
static int	message_zero(void);
static void	end_handler(int signum);

char	g_message[1500];

int	main(void)
{
	struct sigaction	s_end;
	struct sigaction	s_sa;

	ft_printf("Server PID <%d>\n", (int)getpid());
	s_end.sa_handler = end_handler;
	s_sa.sa_sigaction = server_handler;
	s_sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &s_end, NULL) == -1 || \
		sigaction(SIGUSR1, &s_sa, NULL) == -1 || \
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
	while (i < 1500 && g_message[i])
		i++;
	write (1, &g_message, i);
	i = 0;
	while (i < 1500)
		g_message[i++] = 0;
	usleep(500);
	return (0);
}

static void	server_handler(int signum, siginfo_t *info, void *ctx)
{
	static int				octet = 8;
	static unsigned char	c = 0;
	static int				i = 0;

	c = c << 1;
	if (signum == SIGUSR1 && (ctx || !ctx))
		c = c | 1;
	if (--octet != 0)
		return ;
	if (i < 1500)
		g_message[i++] = c;
	else
		i = message_zero();
	if (c == '\0')
	{
		i = message_zero();
		kill(info->si_pid, SIGUSR1);
		ft_printf(" \n\n [End of message]\n [Sending confirmation...]\n");
		ft_printf(" [Confirmation sent]\n");
	}
	octet = 8;
	c = 0;
}

static void	end_handler(int signum)
{
	(void)signum;
	ft_printf("\n [CTRL + c] Server terminated\n");
	exit (EXIT_SUCCESS);
}

// Required code for alternative implementation with linked lists
// 
// #include "../include/minitalk.h"
// 
// t_char_node *mt_chrlst_new(t_char_node **head, char c)
// {
// 	t_char_node *node;
// 
// 	node = (t_char_node *) malloc (sizeof(t_char_node));
// 	if (!node)
// 	{
// 		mt_chrlst_clear(head);
// 		return (NULL);
// 	}
// 	node->character = c;
// 	node->next = NULL;
// 	return (node);
// }
// 
// void	mt_chrlst_add(t_char_node **head, t_char_node *new)
// {
// 	t_char_node	*aux;
// 
// 	if (!*head)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	aux = *head;
// 	while (aux->next)
// 		aux = aux->next;
// 	aux->next = new;
// }
// 
// void mt_chrlst_clear(t_char_node **head)
// {
// 	t_char_node	*aux;
// 	t_char_node	*next;
// 
// 	aux = head;
// 	while (aux)
// 	{
// 		next = aux->next;
// 		free(aux);
// 		aux = next;
// 	}
// 	free(head);
// }
// 
// void	mt_print_list(t_char_node *head)
// {
// 	char	c;
// 
// 	while (head)
// 	{
// 		c = head->character;
// 		write (1, &c, 1);
// 		head = head->next;
// 		ft_printf("\naqui\n");
// 	}
// 	mt_chrlst_clear(head);
// }
