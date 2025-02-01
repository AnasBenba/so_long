/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:35:09 by abenba            #+#    #+#             */
/*   Updated: 2024/12/23 22:35:11 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	*check_format(char format, va_list args, int *count)
{
	int	flag;

	flag = 0;
	if (format == '%')
		ft_putchar('%', count);
	else if (format == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (format == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (format == 'u')
		ft_putnbr_u(va_arg(args, unsigned int), count);
	else if (format == 'x' || format == 'X')
	{
		if (format == 'x')
			ft_puthex(va_arg(args, unsigned int), count, flag);
		else
			ft_puthex_upp(va_arg(args, unsigned int), count, flag);
	}
	else if (format == 'p')
		ft_putaddr(va_arg(args, unsigned long), count, flag);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			check_format(format[i], args, &count);
		}
		else
			ft_putchar(format[i], &count);
		i++;
	}
	va_end(args);
	return (count);
}
