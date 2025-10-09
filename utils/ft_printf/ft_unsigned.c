/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:10:03 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/03/23 16:05:58 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_fd(unsigned int nb, int fd)
{
	int	n;

	n = 0;
	if (nb > 9)
		n += ft_putnbr_fd(nb / 10, fd);
	n += ft_putchar_fd(48 + nb % 10, fd);
	return (n);
}
