/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:47:58 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:19 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_stackpop(t_stack *stack)
{
	t_list	*list;

	list = stack->list;
	if (list)
	{
		stack->list = list->next;
		list->next = NULL;
	}
	return (list);
}
