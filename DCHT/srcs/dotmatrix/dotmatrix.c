/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:20:07 by ijang             #+#    #+#             */
/*   Updated: 2021/11/24 13:06:42 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix.h"

t_matrixstate	*ms_alloc(size_t size)
{
	if (size <= 0 || size > MAXMATRIX)
		return NULL;

	t_matrixstate	*new;

	if (!check_malloc((void *)&new, sizeof(t_matrixstate)))
		return NULL;
	new->matrix_num = size;
	if (!check_malloc((void *)&(new->state), 8 * sizeof(unsigned char *))) {
		free(new);
		return NULL;
	}
	for (size_t i = 0; i < 8; ++i)
		if (!check_calloc((void *)&(new->state[i]), size, sizeof(unsigned char))) {
			while (i > 0)
				free(new->state[i]);
			free(new->state);
			free(new);
			return NULL;
		}
	return new;
}

void			ms_free(t_matrixstate *ms)
{
	for (int i = 0; i < 8; ++i)
		free(ms->state[i]);
	free(ms->state);
	free(ms);
}

void			spi_2byte_write(unsigned char r, unsigned char d)
{
	for (int i = 0; i < 4; ++i) {
		digitalWrite(CLOCK_PIN, LOW);
		digitalWrite(DATA_PIN, 0);
		digitalWrite(CLOCK_PIN, HIGH);
	}
	for (int i = 0; i < 4; ++i) {
		digitalWrite(CLOCK_PIN, LOW);
		digitalWrite(DATA_PIN, r & 0x08);
		digitalWrite(CLOCK_PIN, HIGH);
		r <<= 1;
	}
	for (int i = 0; i < 8; ++i) {
		digitalWrite(CLOCK_PIN, LOW);
		digitalWrite(DATA_PIN, d & 0x80);
		digitalWrite(CLOCK_PIN, HIGH);
		d <<= 1;
	}
}

void			spi_blank_write()
{
	for (int i = 0; i < 16; ++i) {
		digitalWrite(CLOCK_PIN, LOW);
		digitalWrite(DATA_PIN, 0);
		digitalWrite(CLOCK_PIN, HIGH);
	}
}

void			spi_2byte_print(unsigned char r, unsigned char d)
{
	digitalWrite(LOAD_PIN, LOW);
	spi_2byte_write(r, d);
	digitalWrite(LOAD_PIN, HIGH);
}

void			spi_matrix_setting(int size, unsigned char code, unsigned char d)
{
	digitalWrite(LOAD_PIN, LOW);
	for (int i = 0; i < size; ++i)
		spi_2byte_write(code, d);
	digitalWrite(LOAD_PIN, HIGH);
}

void			spi_layer_print(int size, unsigned char layer, unsigned char *d)
{
	digitalWrite(LOAD_PIN, LOW);
	for (int i = 0; i < size; ++i)
		spi_2byte_write(layer, d[i]);
	digitalWrite(LOAD_PIN, HIGH);
}

void			spi_matrix_print(t_matrixstate *ms)
{
	if (!ms)
		return ;
	for (int i = 0; i < 8; ++i)
		spi_layer_print(ms->matrix_num, i + 1, ms->state[i]);
}