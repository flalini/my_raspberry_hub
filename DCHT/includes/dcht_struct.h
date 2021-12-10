/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcht_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:11:53 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 21:42:41 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCHT_STRUCT_H
# define DCHT_STRUCT_H

# include "pin.h"
# include "util.h"
# include "dotmatrix.h"
# include "dotmatrix_add.h"
# include "dht11.h"
# include <errno.h>

typedef struct	s_dcht
{
	t_ms_add		*msa;
	t_dht11			dht11;
	unsigned char	**tmp;
	struct tm		tm;
	unsigned char	sw_flag;
	pthread_t		pid[2];
}				t_dcht;

void		init_dcht(t_dcht *dcht);
void		clear_dcht(t_dcht *dcht);

#endif
