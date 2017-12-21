/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacknew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:47:12 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:18 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stacknew(void *content, size_t size)
{
	t_stack	*stack;

	stack = ft_memalloc(sizeof(t_stack));
	if (stack)
	{
		stack->list = ft_lstnew(content, size);
		stack->pop = ft_stackpop;
		stack->push = ft_stackpush;
	}
	return (stack);
}
