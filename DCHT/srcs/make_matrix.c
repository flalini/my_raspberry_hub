/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:59:03 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 21:55:40 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pin.h"
#include "make_matrix.h"

int		tmp_data_alloc(unsigned char **p, size_t num)
{
	if (num <= 0 || num > MATRIX_NUM)
		return 0;
	if (!check_calloc((void *)&p, 8, sizeof(unsigned char *))) {
		free(p);
		return 0;
	}
	for (size_t i = 0; i < 8; ++i)
		if (!check_calloc((void *)&(p[i]), num, sizeof(unsigned char))) {
			while (i > 0)
				free(p[--i]);
			free(p);
			return 0;
		}
	return 1;
}

void	tmp_data_free(unsigned char **p)
{
	for (int i = 0; i < 8; ++i)
		free(p[i]);
	free(p);
}

int		make_clock(unsigned char **tmp, struct tm *tm)
{
	for (int i = 0; i < 8; ++i) {
		if (tm->tm_mon > 8)
			tmp[i][0] = g_digit[1][i] << 7;
		else
			tmp[i][0] = 0;
		tmp[i][0] |= g_digit[tm->tm_mon % 10 + 1][i] << 3;
		tmp[i][0] |= g_digit[tm->tm_mday / 10][i] >> 1;
		tmp[i][1] = g_digit[tm->tm_mday / 10][i] << 7;
		tmp[i][1] |= g_digit[tm->tm_mday % 10][i] << 3;
		tmp[i][1] |= g_digit[tm->tm_hour / 10][i] >> 1;
		tmp[i][2] = g_digit[tm->tm_hour / 10][i] << 7;
		tmp[i][2] |= g_digit[tm->tm_hour % 10][i] << 3;
		tmp[i][3] = g_digit[tm->tm_min / 10][i] << 5;
		tmp[i][3] |= g_digit[tm->tm_min % 10][i] << 1;
	}
	tmp[7][0] |= 0b100;
	tmp[3][2] |= 0b10;
	tmp[5][2] |= 0b10;
}

int		make_ht(unsigned char **tmp, int h, int t)
{
	for (int i = 0; i < 8; ++i) {
		tmp[i][0] = g_digit[t / 10][i] << 5;
		tmp[i][0] |= g_digit[t % 10][i] << 1;
		tmp[i][2] = g_digit[h / 10][i] << 5;
		tmp[i][2] |= g_digit[h % 10][i] << 1;

		tmp[i][1] = g_symbol[0][i];
		tmp[i][3] = g_symbol[1][i];
	}
}