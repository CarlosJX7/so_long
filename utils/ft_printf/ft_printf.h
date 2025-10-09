/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:09:30 by cinaquiz          #+#    #+#             */
/*   Updated: 2023/03/23 16:06:49 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
int		ft_hex(unsigned int n, char c);
int		ft_putnbr_fd(int n, int fd);
int		ft_ptr(unsigned long n);
int		ft_putstr_fd(char *s, int fd);
int		ft_unsigned_fd(unsigned int nb, int fd);
#endif
