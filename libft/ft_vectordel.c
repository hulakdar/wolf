/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectordel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:58:32 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:34 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vectordel(t_vector *vector)
{
	if (vector && vector->array)
	{
		free(vector->array);
		vector->array = NULL;
	}
}
