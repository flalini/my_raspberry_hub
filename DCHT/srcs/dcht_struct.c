/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcht_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:07:51 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 22:33:04 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dcht_struct.h"
#include "make_matrix.h"

void	init_dcht(t_dcht *dcht)
{
	if (check_malloc((void **)&(dcht->msa), sizeof(t_ms_add))){
		if (errno)
			perror("");
		exit(errno);
	}
	dcht->msa->ms = ms_alloc(4);
	if (!(dcht->msa->ms)) {
		spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
		if (errno)
			perror("");
		exit(errno);
	}
	if (!tmp_data_alloc(dcht->tmp, MATRIX_NUM)) {
		ms_free(dcht->msa->ms);
		spi_matrix_setting(MATRIX_NUM, SHUTDOWN, 0x00);
		if (errno)
			perror("");
		exit(errno);
	}
	matrix_change(dcht->msa, dcht->tmp);
	spi_matrix_change(dcht->msa);
	spi_matrix_print(dcht->msa->ms);
}

void	clear_dcht(t_dcht *dcht) {
	ms_free(dcht->msa->ms);
	tmp_data_free(dcht->tmp);
}
