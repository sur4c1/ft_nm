/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bufclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ***REMOVED*** <***REMOVED***@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:58:18 by ***REMOVED***            #+#    #+#             */
/*   Updated: 2022/12/01 16:17:37 by ***REMOVED***           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_buff.h"

void	ft_bufclear(void *buf)
{
	if (!buf)
		return ;
	if (((t_buff *) buf)->data)
		free(((t_buff *) buf)->data);
	((t_buff *) buf)->data = NULL;
	((t_buff *) buf)->len = 0;
	free(buf);
}
