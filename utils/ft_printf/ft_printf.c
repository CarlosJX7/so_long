/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:17:54 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/03/23 16:05:38 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static void	ft_ini(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

static int	ft_print_types(va_list args, char c)
{
	if (c == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (c == 'X')
		return (ft_hex(va_arg(args, unsigned int), c));
	if (c == 'x')
		return (ft_hex(va_arg(args, unsigned int), c));
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'u')
		return (ft_unsigned_fd(va_arg(args, unsigned int), 1));
	if (c == 'p')
		return (ft_ptr(va_arg(args, unsigned long)));
	return (-1);
}

static int	ft_print_args(va_list args, char const *ph, int len)
{
	int	i;
	int	r;
	int	n;

	ft_ini(&r, &i);
	while (i < len)
	{
		if (ph[i] == '%')
		{
			i++;
			n = ft_print_types(args, ph[i]);
			if (n < 0)
				return (-1);
			else
				r = r + n;
		}
		else
		{
			if (write(1, &ph[i], 1) < 0)
				return (-1);
			r++;
		}
		i++;
	}
	return (r);
}

int	ft_printf(char const *ph, ...)
{
	int		len;
	va_list	args;
	int		n;

	len = ft_strlen(ph);
	va_start(args, ph);
	n = ft_print_args(args, ph, len);
	va_end(args);
	return (n);
}
