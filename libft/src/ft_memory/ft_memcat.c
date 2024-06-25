/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyyyy <yyyyyyyy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:46:52 by yyyyyyyy          #+#    #+#             */
/*   Updated: 2024/06/25 10:38:06 by yyyyyyyy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_memory.h"

void	*ft_memcat(const void *mem1, const void *mem2, size_t len1, size_t len2)
{
	void	*res;
	void	*ptr;

	res = ft_calloc(len1 + len2, 1);
	if (!res)
		return (NULL);
	ptr = res;
	while (len1-- && mem1)
		*(char *)(ptr++) = *(char *)(mem1++);
	while (len2-- && mem2)
		*(char *)(ptr++) = *(char *)(mem2++);
	return (res);
}
