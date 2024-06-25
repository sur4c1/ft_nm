/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:22:00 by ***REMOVED***            #+#    #+#             */
/*   Updated: 2022/11/28 08:39:16 by ***REMOVED***           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_check.h"

int	ft_isprint(int c)
{
	return (
		(c >= 32 && c < 127)
	);
}