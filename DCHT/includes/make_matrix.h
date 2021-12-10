/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_matrix.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:13:47 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 22:43:53 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_MATRIX_H
# define MAKE_MATRIX_H

#include "pin.h"
# include "util.h"
# include <time.h>

int		tmp_data_alloc(unsigned char **p, size_t num);
void	tmp_data_free(unsigned char **p);
void	make_clock(unsigned char **tmp, struct tm *tm);
void	make_ht(unsigned char **tmp, int h, int t);

# endif