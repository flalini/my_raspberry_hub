/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:07:57 by ijang             #+#    #+#             */
/*   Updated: 2021/11/05 01:37:48 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOTMATRIX_H
# define DOTMATRIX_H

# include "util.h"
# include <wiringPi.h>

# define DATA			12
# define CLOCK			14
# define LOAD			10

# define DECODE_MODE	0x09
# define INTENSITY		0x0A
# define SCAN_LIMIT		0x0B
# define SHUTDOWN		0x0C
# define DISPLAY_TEST	0x0F

# define MAXMATRIX		4

typedef struct	s_matrixstate
{
	int				matrix_num;
	unsigned char	**state;
	//state[layer][matrix_num]
}				t_matrixstate;

t_matrixstate	*ms_alloc(size_t size);
void			ms_free(t_matrixstate *ms);
void			spi_2byte_write(unsigned char r, unsigned char d);
void			spi_blank_write();
void			spi_2byte_print(unsigned char r, unsigned char d);
void			spi_layer_print(int size, unsigned char layer, unsigned char *d);
void			spi_matrix_print(t_matrixstate *ms);
void			my_setup();

#endif
