/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_helpers_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 16:59:52 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/02 17:04:57 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wolf_is_wall(t_map *map, int m_y, int m_x)
{
	t_sector sect;

	sect.tex = wolf_get_sector(map, m_y, m_x);
	return (sect.sect.is_wall);
}
