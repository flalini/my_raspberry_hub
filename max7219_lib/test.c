/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:14:01 by ijang             #+#    #+#             */
/*   Updated: 2021/11/10 19:30:43 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/dotmatrix.h"
#include <errno.h>

int		main(void)
{
	t_matrixstate	*ms;
	
	errno = 0;
	if (wiringPiSetup() < 0)
		exit(-1);
	my_setup();
	ms = ms_alloc(1);
	if (!ms) {
		spi_2byte_print(SHUTDOWN, 0x00);
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
	spi_2byte_print(SHUTDOWN, 0x00);
	ms_free(ms);
	return 0;
}