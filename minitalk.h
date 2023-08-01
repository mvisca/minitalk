/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:56:53 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/01 19:41:28 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <libftprintf.h>

struct s_chrlst
{
	struct s_chrlst			*next;
	char					character;
} ;

typedef struct s_chrlst		t_chrlst;

struct	s_signals
{
	int						current_bit;
	t_chrlst				*head;
	char					character;
} ;

typedef struct s_signals	t_signals;

#endif
