/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyyyy <yyyyyyyy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:50:22 by yyyyyyyy          #+#    #+#             */
/*   Updated: 2024/06/25 10:38:05 by yyyyyyyy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/_ft_printf.h"

t_buff	*s(va_list lst, t_flag *flag)
{
	t_buff	*ret;
	char	*data;
	char	*tmp;

	ret = ft_calloc(1, sizeof (t_buff));
	data = va_arg(lst, char *);
	if (data == NULL)
		ret->data = ft_strdup("(null)");
	else
		ret->data = ft_strdup(data);
	if (flag->precision >= 0)
	{
		tmp = ft_substr(ret->data, 0, flag->precision);
		free(ret->data);
		ret->data = tmp;
	}
	ret->len = ft_strlen(ret->data);
	return (ret);
	(void) flag;
}
