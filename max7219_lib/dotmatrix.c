/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:20:07 by ijang             #+#    #+#             */
/*   Updated: 2021/11/02 02:45:34 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix.h"

t_matrixstate	*ms_alloc(size_t size)
{
	if (size <= 0 || size > MAXMATRIX)
		return (NULL);

	t_matrixstate	*new;

	if (!check_malloc((void *)&new, sizeof(t_matrixstate)))
		return (NULL);
	new->matrix_num = size;
	if (!check_malloc((void *)&(new->state), 8 * sizeof(unsigned char *))) {
		free(new);
		return (NULL);
	}
	for (size_t i = 0; i < 8; ++i)
		if (!check_calloc((void *)&(new->state[i]), size, sizeof(unsigned char))) {
			while (i > 0)
				free(new->state[i]);
			free(new->state);
			free(new);
			return (NULL);
		}
	return (new);
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
		digitalWrite(CLOCK, LOW);
		digitalWrite(DATA, 0);
		digitalWrite(CLOCK, HIGH);
	}
	for (int i = 0; i < 4; ++i) {
		digitalWrite(CLOCK, LOW);
		digitalWrite(DATA, r & 0x08);
		digitalWrite(CLOCK, HIGH);
		r <<= 1;
	}
	for (int i = 0; i < 8; ++i) {
		digitalWrite(CLOCK, LOW);
		digitalWrite(DATA, d & 0x80);
		digitalWrite(CLOCK, HIGH);
		d <<= 1;
	}
}

void			spi_2byte_print(unsigned char r, unsigned char d)
{
	digitalWrite(LOAD, LOW);
	spi_2byte_write(r, d);
	digitalWrite(LOAD, HIGH);
}

void			spi_layer_print(int size, unsigned char layer, unsigned char *d)
{
	digitalWrite(LOAD, LOW);
	for (int i = 0; i < size; ++i)
		spi_2byte_write(layer, d[i]);
	digitalWrite(LOAD, HIGH);
}

void			spi_matrix_print(t_matrixstate *ms)
{
	for (int i = 0; i < 8; ++i)
		spi_layer_print(ms->matrix_num, i + 1, ms->state[i]);
}

void			my_setup()
{
	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	spi_2byte_print(DECODE_MODE, 0x00);
	spi_2byte_print(INTENSITY, 0x08);
	spi_2byte_print(SCAN_LIMIT, 0x07);
	spi_2byte_print(SHUTDOWN, 0x01);
	spi_2byte_print(DISPLAY_TEST, 0x00);
}