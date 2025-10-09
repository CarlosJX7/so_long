/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cainaqui <cainaqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:14:17 by cainaqui          #+#    #+#             */
/*   Updated: 2022/09/01 20:04:32 by cainaqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*memoria;

	if ((nitems == SIZE_MAX) || (size == SIZE_MAX))
		return (NULL);
	memoria = (void *)malloc(nitems * size);
	if (!memoria)
		return (NULL);
	ft_bzero(memoria, (nitems * size));
	return ((void *)memoria);
}
