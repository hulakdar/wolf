/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:31:48 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:44 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vectorinit(t_vector *dynarr, size_t size, size_t init)
{
	size_t		new_size;

	ft_bzero(dynarr, sizeof(t_vector));
	new_size = 32;
	while (init * size > new_size)
		new_size = new_size << 1;
	dynarr->array = ft_memalloc(new_size * size);
	dynarr->last = new_size - 1;
	dynarr->size = size;
	dynarr->back = 0;
}
