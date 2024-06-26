/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyyyy <yyyyyyyy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:37:24 by yyyyyyyy          #+#    #+#             */
/*   Updated: 2024/06/25 10:38:06 by yyyyyyyy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECK_H
# define FT_CHECK_H

/* Return true if c is a whitespace, false otherwise */
int		ft_isspace(char c);

/* Return true if c is a letter, false otherwise */
int		ft_isalpha(int c);

/* Return true if c is a digit, false otherwise */
int		ft_isdigit(int c);

/* Return true if c is a letter or a digit, false otherwise */
int		ft_isalnum(int c);

/* Return true if c is an ascii char, false otherwise */
int		ft_isascii(int c);

/* Return true if c is a printable char, false otherwise */
int		ft_isprint(int c);

#endif
