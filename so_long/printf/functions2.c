/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:35:29 by abenba            #+#    #+#             */
/*   Updated: 2024/12/25 17:50:20 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_puthex_upp(unsigned int c, int *count, int flag)
{
	char	*hex;
	int		i;

	hex = "0123456789ABCDEF";
	i = 0;
	if (c == 0 && flag != 0)
		return ;
	else if (c == 0 && flag == 0)
	{
		ft_putchar('0', count);
	}
	else
	{
		flag = 1;
		ft_puthex_upp(c / 16, count, flag);
		i = c % 16;
		ft_putchar(hex[i], count);
	}
}

void	ft_putaddr(unsigned long c, int *count, int flag)
{
	int		i;
	char	*hex;

	i = 0;
	hex = "0123456789abcdef";
	if (c == 0 && flag == 0)
		ft_putstr("(nil)", count);
	else
	{
		if (c == 0 && flag != 0)
		{
			ft_putstr("0x", count);
			return ;
		}
		else
		{
			flag = 1;
			ft_putaddr(c / 16, count, flag);
			i = c % 16;
			ft_putchar(hex[i], count);
		}
	}
}
