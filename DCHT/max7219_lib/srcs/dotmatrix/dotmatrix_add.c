/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 01:38:31 by ijang             #+#    #+#             */
/*   Updated: 2021/12/09 00:19:51 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix_add.h"

void	spi_layer_change(int size, unsigned char layer, unsigned char *d, unsigned char c)
{
	digitalWrite(LOAD_PIN, LOW);
	while (size--) {
		if (c & 1u << size)
			spi_2byte_write(layer, *d);
		else
			spi_blank_write();
		++d;
	}
	digitalWrite(LOAD_PIN, HIGH);
}

void	spi_matrix_change(t_ms_add *ms_add)
{
	if (!ms_add || !(ms_add->ms))
		return ;
	t_matrixstate	*ms = ms_add->ms;
	for (int i = 0; i < 8; ++i) {
		if (ms_add->change[i])
			spi_layer_change(ms->matrix_num, i + 1, ms->state[i], ms_add->change[i]);
		ms_add->change[i] = 0;
	}
}

void	layer_change(t_ms_add *ms_add, unsigned char layer, unsigned char *d)
{
	printf("[%p]\n", d);
	if (!ms_add || !d)
		return ;
	t_matrixstate	*ms = ms_add->ms;
	unsigned char	flag = 0;

	for (int i = 0; i < ms->matrix_num; ++i) {
		flag <<= 1;
		if (ms->state[layer][i] != d[i]) {
			ms->state[layer][i] = d[i];
			flag += 1;
		}
	}
	ms_add->change[layer] |= flag;
}

void	matrix_change(t_ms_add *ms_add, unsigned char **d)
{
	printf("m[%p]\n", d);
	if (!ms_add || !d)
		return ;

	for (int i = 0; i < 8; ++i) {
		printf("layer[%d][%p][%p]\n", i, d[i], (d + i));
		layer_change(ms_add, i, d + i);
	}
}