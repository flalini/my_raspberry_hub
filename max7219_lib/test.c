/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:14:01 by ijang             #+#    #+#             */
/*   Updated: 2021/11/02 01:32:43 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix.h"
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
	ms->state[0] = 0b00000000;
	ms->state[1] = 0b01000000;
	ms->state[2] = 0b01100000;
	ms->state[3] = 0b01110000;
	ms->state[4] = 0b01111100;
	ms->state[5] = 0b01111110;
	ms->state[6] = 0b01111111;
	ms->state[7] = 0b01111111;
	spi_matrix_print(ms);
	spi_2byte_print(SHUTDOWN, 0x00);
	exit(0);
}