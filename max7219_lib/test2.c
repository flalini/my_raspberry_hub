/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:28:23 by ijang             #+#    #+#             */
/*   Updated: 2021/11/13 17:22:07 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix_add.h"
#include <errno.h>

#define MATRIX_NUM	1

void			my_setup()
{
	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(LOAD, OUTPUT);
	spi_layer_print(MATRIX_NUM, DECODE_MODE, 0x00);
	//	don't use Decode-Mode
	spi_layer_print(MATRIX_NUM, INTENSITY, 0x08);
	//	use 0x08 Intensity level (0x00 to 0x0F)
	spi_layer_print(MATRIX_NUM, SCAN_LIMIT, 0x07);
	//	use full Scan-Limit Display digit (0 to 7)
	spi_layer_print(MATRIX_NUM, SHUTDOWN, 0x01);
	//	Normal Operation
	spi_layer_print(MATRIX_NUM, DISPLAY_TEST, 0x00);
	//	Normal Operation
}

void	ms_init(t_ms_add *ms)
{
	ms->ms = ms_alloc(4);
	if (!(ms->ms)) {
		spi_layer_print(MATRIX_NUM, SHUTDOWN, 0x00);
		if (errno)
			perror("");
		exit(errno);
	}
	for (int i = 0; i < 8; ++i) {
		ms->change[i] = 0;
		for (int j = 0; j < ms->ms->matrix_num; ++j)
			ms->ms->state[i][j] = 0b00000001;
	}
}

int		main(void)
{
	t_ms_add		ms;
	unsigned char	d[4];
	
	errno = 0;
	if (wiringPiSetup() < 0)
		exit(-1);
	my_setup();
	ms_init(&ms);
	spi_matrix_print(ms.ms);
	delay(2000);
	for (int i = 1; i < 8; ++i) {
		for (int j = 0; j < 4; ++j)
			d[j] = 0b00000001;
		for (int j = 0; j < i + 3; ++j) {
			if (j < i)
				d[0] <<= 1;
			if (j > 0 && j < i + 1)
				d[1] <<= 1;
			if (j > 1 && j < i + 2)
				d[2] <<= 1;
			if (j > 2 && j < i + 3)
				d[3] <<= 1;
			layer_change(&ms, i, d);
			spi_matrix_change(&ms);
			delay(200);
		}
	}
	delay(2000);
	spi_layer_print(MATRIX_NUM, SHUTDOWN, 0x00);
	ms_free(ms.ms);
	return 0;
}