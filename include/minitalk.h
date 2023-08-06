/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:56:53 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/05 02:35:36 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <libft.h>


// Linked list of chars node's struct
typedef struct	s_char_node
{
	char					character;
	struct s_char_node			*next;
} t_char_node;

// Struct to rebuild and store chars
typedef struct	s_mssg
{
	int						current_bit;
	char					character;
	t_char_node				*head;
} t_mssg;

// Instance of strcut t_mssg to rebuild and store chars
extern t_mssg	g_mssg;

// server_utils.c
t_char_node *mt_chrlst_new(t_char_node *head, char c);
t_char_node	*mt_chrlst_add(t_char_node **head, t_char_node *new);
void 		mt_chrlst_clear(t_char_node *head);
void		mt_print_list(t_char_node *head);

#endif
