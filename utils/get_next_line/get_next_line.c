/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:29:04 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/05/12 16:26:22 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_procesar_linea_aux(char **dir_memoria, char *dir_salto)
{
	char	*new_str;
	char	*tmp;

	if (dir_salto)
	{
		new_str = ft_substr(*dir_memoria, 0, dir_salto - *dir_memoria + 1);
		tmp = ft_substr(dir_salto + 1, 0, ft_strlen(dir_salto + 1));
		free(*dir_memoria);
		*dir_memoria = tmp;
	}
	else
	{
		if (*dir_memoria && **dir_memoria)
			new_str = ft_substr(*dir_memoria, 0, ft_strlen(*dir_memoria));
		else
			new_str = NULL;
		free(*dir_memoria);
		*dir_memoria = NULL;
	}
	return (new_str);
}

char	*ft_procesar_linea(char	*cadena)
{
	static char	*dir_memoria;
	char		*tmp;
	char		*dir_salto;

	if (!cadena && !dir_memoria)
		return (NULL);
	if (cadena)
	{
		tmp = ft_strjoin(dir_memoria, cadena);
		free(dir_memoria);
		dir_memoria = tmp;
	}
	dir_salto = ft_strchr(dir_memoria, '\n');
	return (ft_procesar_linea_aux(&dir_memoria, dir_salto));
}

char	*ft_bucle_salto_parte2(char *buffer, char *tmp, int char_read)
{
	char	*joined_string;

	buffer[char_read] = '\0';
	joined_string = ft_strjoin(tmp, buffer);
	free(tmp);
	tmp = joined_string;
	free(buffer);
	return (tmp);
}

char	*ft_bucle_salto(int fd)
{
	int		char_read;
	char	*tmp;
	char	*buffer;

	tmp = NULL;
	while (1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			free(tmp);
			return (NULL);
		}
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(tmp);
			free(buffer);
			return (NULL);
		}
		tmp = ft_bucle_salto_parte2(buffer, tmp, char_read);
		if (ft_strchr(tmp, '\n') || char_read == 0)
			break ;
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	char	*resultado;
	char	*linea_sin_procesar;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	linea_sin_procesar = ft_bucle_salto(fd);
	if (!linea_sin_procesar)
		return (NULL);
	resultado = ft_procesar_linea(linea_sin_procesar);
	free(linea_sin_procesar);
	return (resultado);
}
