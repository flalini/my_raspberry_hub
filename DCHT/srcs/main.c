/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:22:51 by ijang             #+#    #+#             */
/*   Updated: 2021/12/11 16:05:34 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dcht.h"

void			my_setup(unsigned char brightness)
{
	pinMode(SW_PIN, INPUT);
	pinMode(DATA_PIN, OUTPUT);
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(LOAD_PIN, OUTPUT);
	spi_matrix_setting(MATRIX_NUM, DECODE_MODE, 0x00);
	//	don't use Decode-Mode
	spi_matrix_setting(MATRIX_NUM, INTENSITY, brightness);
	//	use 0x08 Intensity level (0x00 to 0x0F)
	spi_matrix_setting(MATRIX_NUM, SCAN_LIMIT, 0x07);
	//	use full Scan-Limit Display digit (0 to 7)
	spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x01);
	//	Normal Operation
	spi_matrix_setting(MATRIX_NUM, DISPLAY_TEST, 0x00);
	//	Normal Operation
}

void	error_exit(t_dcht *dcht) {
	spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
	clear_dcht(dcht);
	if (errno)
		perror("");
	exit(errno);
}

void			display_time(t_dcht *dcht)
{
	time_t		tim;
	struct tm	*tm;

	tim = time(NULL);
	tm = localtime(&tim);
	dcht->tm = *tm;
	make_clock(dcht->tmp, tm);
	matrix_change(dcht->msa, dcht->tmp);
	spi_matrix_change(dcht->msa);
	while (!(dcht->sw_flag)) {
		delay(1);
		tim = time(NULL);
		tm = localtime(&tim);
		if (tm->tm_min != dcht->tm.tm_min ||
				tm->tm_hour != dcht->tm.tm_hour ||
				tm->tm_yday != dcht->tm.tm_yday ||
				((tm->tm_sec ^ dcht->tm.tm_sec) & 1)) {
			dcht->tm = *tm;
			make_clock(dcht->tmp, tm);
			matrix_change(dcht->msa, dcht->tmp);
			spi_matrix_change(dcht->msa);
		}
	}
	dcht->sw_flag = 0;
}

void			display_ht(t_dcht *dcht)
{
	dcht->dht11.change = 0;
	make_ht(dcht->tmp, dcht->dht11.data.val[0], dcht->dht11.data.val[2]);
	matrix_change(dcht->msa, dcht->tmp);
	spi_matrix_change(dcht->msa);
	while (!(dcht->sw_flag)) {
		delay(1);
		if (dcht->dht11.change) {
			dcht->dht11.change = 0;
			make_ht(dcht->tmp, dcht->dht11.data.val[0], dcht->dht11.data.val[2]);
			matrix_change(dcht->msa, dcht->tmp);
			spi_matrix_change(dcht->msa);
		}
	}
	dcht->sw_flag = 0;
}

int		main(int argc, char **argv)
{
	t_dcht			dcht;
	unsigned char	brightness = 0x08;
	unsigned char	tmp;

	errno = 0;
	if (wiringPiSetup() < 0)
		exit(-1);
	if (argc == 2) {
		tmp = atoi(argv[1]);
		if (tmp >= 0x00 && tmp <= 0x0f)
			brightness = tmp;
	}
	my_setup(brightness);
	init_dcht(&dcht);

	if ((errno = dht11_thread_start(&(dcht.dht11), &(dcht.pid[0]))))
		error_exit(&dcht);
	if ((errno = switch_thread_start(&(dcht.sw_flag), &(dcht.pid[1])))) {
		pthread_cancel(dcht.pid[0]);
		pthread_join(dcht.pid[0], NULL);
		error_exit(&dcht);
	}

	while (1) {
		display_time(&dcht);
		display_ht(&dcht);
	}

	return 0;
}
