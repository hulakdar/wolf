/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectornew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:16:02 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vectornew(size_t size, size_t init)
{
	t_vector	dynarr;

	ft_vectorinit(&dynarr, size, init);
	return (dynarr);
}
