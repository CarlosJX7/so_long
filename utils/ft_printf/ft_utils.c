/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:10:20 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/03/23 16:06:04 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) < 0)
		return (-1);
	else
		return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (write(fd, "(null)", 6));
	else
	{
		return (write(fd, s, ft_strlen(s)));
	}	
}

int	ft_putnbr_fd(int n, int fd)
{
	long int	copia;
	int			r;

	r = 0;
	copia = n;
	if (copia < 0)
	{
		copia = (copia * -1);
		r += write(fd, "-", 1);
	}
	if (copia > 9)
	{
		r += ft_putnbr_fd(copia / 10, fd);
		r += ft_putchar_fd((copia % 10) + '0', fd);
	}
	else
		r += ft_putchar_fd(copia + '0', fd);
	return (r);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
