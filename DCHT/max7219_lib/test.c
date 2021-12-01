/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:14:01 by ijang             #+#    #+#             */
/*   Updated: 2021/12/01 23:18:54 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix.h"
#include <errno.h>

#define MATRIX_NUM	1

void			my_setup()
{
	pinMode(DATA_PIN, OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(LOAD_PIN, OUTPUT);
	spi_matrix_setting(MATRIX_NUM, DECODE_MODE, 0x00);
	//	don't use Decode-Mode
	spi_matrix_setting(MATRIX_NUM, INTENSITY, 0x08);
	//	use 0x08 Intensity level (0x00 to 0x0F)
	spi_matrix_setting(MATRIX_NUM, SCAN_LIMIT, 0x07);
	//	use full Scan-Limit Display digit (0 to 7)
	spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x01);
	//	Normal Operation
	spi_matrix_setting(MATRIX_NUM, DISPLAY_TEST, 0x00);
	//	Normal Operation
}

int		main(void)
{
	t_matrixstate	*ms;
	
	errno = 0;
	if (wiringPiSetup() < 0)
		exit(-1);
	my_setup();
	ms = ms_alloc(MATRIX_NUM);
	if (!ms) {
		spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
		if (errno)
			perror("");
		exit(errno);
	}
	/*
	ms->state[0][0] = 0b00000000;
	ms->state[1][0] = 0b01000000;
	ms->state[2][0] = 0b01100000;
	ms->state[3][0] = 0b01110000;
	ms->state[4][0] = 0b01111000;
	ms->state[5][0] = 0b01111100;
	ms->state[6][0] = 0b01111110;
	ms->state[7][0] = 0b01111111;*/
	ms->state[0][0] = 0b00000001;
	ms->state[1][0] = 0b00000001;
	ms->state[2][0] = 0b00000001;
	ms->state[3][0] = 0b00000001;
	ms->state[4][0] = 0b00000001;
	ms->state[5][0] = 0b00000001;
	ms->state[6][0] = 0b00000001;
	ms->state[7][0] = 0b00000001;
	spi_matrix_print(ms);
	delay(2000);
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < i; ++j) {
			ms->state[i][0] <<= 1;
			spi_matrix_print(ms);
			delay(200);
		}
	delay(2000);
	spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
	ms_free(ms);
	return 0;
}