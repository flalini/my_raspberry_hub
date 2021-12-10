/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_matrix.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:13:47 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 18:35:15 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_MATRIX_H
# define MAKE_MATRIX_H

# include "util.h"
# include <time.h>

extern unsigned char	g_digit[10][8];
extern unsigned char	g_symbol[2][8];

int		tmp_data_alloc(unsigned char **p, size_t num);
void	tmp_data_free(unsigned char **p);
int		make_clock(unsigned char **tmp, struct tm *tm);
int		make_ht(unsigned char **tmp, int h, int t);

# endif