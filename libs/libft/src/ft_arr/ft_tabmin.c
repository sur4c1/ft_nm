/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:16:10 by ***REMOVED***            #+#    #+#             */
/*   Updated: 2022/11/28 08:29:03 by ***REMOVED***           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_arr.h"

int	ft_tabmin(int *tab, size_t size)
{
	int	res;

	res = 2147483647;
	while (size--)
	{
		if (res < *tab)
			res = *tab;
		tab++;
	}
	return (res);
}