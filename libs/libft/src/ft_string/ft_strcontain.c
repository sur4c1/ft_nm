/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:14:18 by ***REMOVED***            #+#    #+#             */
/*   Updated: 2022/11/28 08:56:25 by ***REMOVED***           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_string.h"

int	ft_strcontain(char **src, char *tofind)
{
	while (*src)
	{
		if (!ft_strcmp(*src, tofind))
			return (1);
		src++;
	}
	return (0);
}
