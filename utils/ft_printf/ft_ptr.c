/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:09:47 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/03/23 16:05:51 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_ini_long(unsigned long n)
{
	if (n > 0)
		return ("0123456789abcdef");
	else
		return ("fedcba9876543210");
}

static int	ft_long_hex(unsigned long n)
{
	char			*h;
	unsigned char	*buffer;
	int				i;
	int				r;

	buffer = malloc(16 * sizeof(n) + 1);
	if (!buffer || buffer == NULL || sizeof(n) == 0)
		return (-1);
	buffer[16] = '\0';
	i = 0;
	h = ft_ini_long(n);
	r = write(1, "0x", 2);
	while (n > 0)
	{
		buffer[i] = n % 16;
		n = n / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		r += write(1, &h[buffer[i]], 1);
	}
	free(buffer);
	return (r);
}

int	ft_ptr(unsigned long n)
{
	int	r;

	r = 0;
	if (n == 0)
		r += write(1, "0x0", 3);
	else
		r += ft_long_hex(n);
	return (r);
}
