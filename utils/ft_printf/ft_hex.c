/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:09:11 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/04/05 16:30:56 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_ini(unsigned int n, char c)
{
	if (c == 'X')
	{
		if (n > 0)
			return ("0123456789ABCDEF");
		else
			return ("FEDCBA9876543210");
	}
	else
	{
		if (n > 0)
			return ("0123456789abcdef");
		else
			return ("fedcba9876543210");
	}
}

int	ft_hex_write(unsigned int n, char c)
{
	char			*h;
	unsigned char	*buffer;
	int				i;
	int				r;

	r = 0;
	h = ft_ini(n, c);
	buffer = malloc(8 * sizeof(n) + 1);
	if (!buffer)
		return (-1);
	buffer[8] = '\0';
	i = 0;
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

int	ft_hex(unsigned int n, char c)
{
	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	else
		return (ft_hex_write(n, c));
}
