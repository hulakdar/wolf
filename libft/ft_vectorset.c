/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:14:36 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:24:35 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vectorset(t_vector *vect, size_t index, void *content)
{
	void		*newarr;
	size_t		new_size;
	size_t		size;

	if (!vect)
		return (NULL);
	size = vect->size;
	if (index > vect->last)
	{
		new_size = vect->last + 1;
		while (new_size < index + 2)
			new_size <<= 1;
		newarr = ft_memalloc(new_size * vect->size);
		if (vect->array)
		{
			ft_quickmove(newarr, vect->array, (vect->last + 1) * vect->size);
			free(vect->array);
		}
		vect->array = newarr;
		vect->last = new_size - 1;
	}
	return (ft_memmove(vect->array + (size * index), content, size));
}
