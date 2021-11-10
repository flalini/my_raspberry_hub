/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 01:38:31 by ijang             #+#    #+#             */
/*   Updated: 2021/11/05 02:18:03 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix_add.h"

void	spi_layer_change(int size, unsigned char layer, unsigned char *d, unsigned char c)
{
	digitalWrite(LOAD, LOW);
	while (size--)
	{
		if (c & 1u << size)
			spi_2byte_write(layer, *d);
		else
			spi_blank_write();
		++d;
	}
	digitalWrite(LOAD, HIGH);
}

void	spi_matrix_change(t_ms_add *ms_add)
{
	if (!ms_add || !(ms_add->ms))
		return ;
	t_matrixstate	*ms = ms_add->ms;
	for (int i = 0; i < 8; ++i)
	{
		if (ms_add->change[i])
			spi_layer_change(ms->matrix_num, i + 1, ms->state[i], ms_add->change[i]);
		ms_add->change[i] = 0;
	}
}

void	matrix_change(t_ms_add *ms_add, unsigned char **d)
{
	if (!ms_add || !d)
		return ;
	t_matrixstate	*ms = ms_add->ms;
	unsigned char	flag;
	for (int i = 0; i < 8; ++i)
	{
		flag = 0;
		for (int j = 0; i < ms->matrix_num; ++i)
		{
			flag <<= 1;
			if (ms->state[i][j] != d[i][j])
			{
				ms->state[i][j] = d[i][j];
				flag += 1;
			}
		}
		ms_add->change[i] |= flag;
	}
}