/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotmatrix_add.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 01:38:28 by ijang             #+#    #+#             */
/*   Updated: 2021/11/10 19:36:25 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOTMATRIX_ADD_H
# define DOTMATRIX_ADD_H

# include "dotmatrix.h"

typedef struct	s_ms_add
{
	t_matrixstate	*ms;
	unsigned char	change[8];
	//state[layer]
}				t_ms_add;

void			spi_layer_change(int size, unsigned char layer, unsigned char *d, unsigned char c);
void			spi_matrix_change(t_ms_add *ms_add);
void			layer_change(t_ms_add *ms_add, unsigned char layer, unsigned char *d);
void			matrix_change(t_ms_add *ms_add, unsigned char **d);

#endif
