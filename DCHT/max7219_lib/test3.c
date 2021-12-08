/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:24:02 by ijang             #+#    #+#             */
/*   Updated: 2021/12/09 00:17:45 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dotmatrix_add.h"
#include <errno.h>

#define MATRIX_NUM	4

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

void	ms_init(t_ms_add *ms)
{
	ms->ms = ms_alloc(4);
	if (!(ms->ms)) {
		spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
		if (errno)
			perror("");
		exit(errno);
	}
	unsigned char	tmp_data[8][4]; 
	printf("[%p]\n", tmp_data);
	for (int i = 0; i < 8; i++)
	{
		printf("i[%p]", tmp_data[i]);
		for (int j = 0; j < 4; j++)
		{
			printf("[%hhu]", tmp_data[i][j]);
			tmp_data[i][j] = 0;
		}
		printf("\n");
	}
	matrix_change(ms, tmp_data);
	spi_matrix_change(ms);
}

int		main(void)
{
	t_ms_add		ms;
	unsigned char	d[8][4];
	
	errno = 0;
	if (wiringPiSetup() < 0)
		exit(-1);
	my_setup();
	printf("test1\n");
	ms_init(&ms);
	printf("test2\n");
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			d[i][j] = 0;
		}
	delay(2000);

	//unsigned char [8][4] 배열에 원하는 데이터 담아서
	//matrix_change(&ms, 데이터);
	//spi_matrix_change(&ms);
	//한번 해보세요.

	d[0][0] = 0b00000000;
	d[1][0] = 0b00000000;
	d[2][0] = 0b11100100;
	d[3][0] = 0b10101100;
	d[4][0] = 0b10100100;
	d[5][0] = 0b10100100;
	d[6][0] = 0b11101110;
	d[7][0] = 0b00000000;
	printf("test3\n");
	matrix_change(&ms, d);
	printf("test4\n");
	spi_matrix_change(&ms);
	printf("test5\n");

	delay(2000);
	spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
	ms_free(ms.ms);
	return 0;
}