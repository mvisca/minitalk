/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:56:53 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/16 14:04:48 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/include/libft.h"

// Struct to rebuild and store chars
typedef struct	s_mssg
{
	int					current_bit;
	int					character;
} t_mssg;

#endif
