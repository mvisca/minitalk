/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:42:07 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/01 19:48:05 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libftprintf.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	len_src = ft_strlen((char *)src);
	len_dest = ft_strlen(dest);
	if (size == 0)
		return (len_src);
	else if (size < len_dest)
		return (len_src + size);
	else
	{
		len_src += len_dest;
		i = 0;
		while (src[i] && (len_dest + i) < size - 1)
		{
			dest[len_dest + i] = src[i];
			i++;
		}
		dest[len_dest + i] = '\0';
	}
	return (len_src);
}
