/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectordestruct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:23:15 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:41 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vectordestruct(t_vector *ptr)
{
	size_t		cunt;
	void		*content;

	if (!ptr)
		return ;
	cunt = 0;
	while (cunt < ptr->back)
	{
		if ((content = *(void **)(ptr->array + cunt * ptr->size)))
			free(content);
		cunt++;
	}
	return (ft_vectordel(ptr));
}
