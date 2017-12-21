/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorpopback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:24:24 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:46 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vectorpopback(t_vector *vect)
{
	if (!vect->back)
		return (NULL);
	vect->back -= 1;
	return (ft_vectorget(vect, vect->back));
}
