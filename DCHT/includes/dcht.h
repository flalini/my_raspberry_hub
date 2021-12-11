/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcht.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:04:09 by ijang             #+#    #+#             */
/*   Updated: 2021/12/11 16:05:59 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCHT_H
# define DCHT_H

# include "pin.h"
# include "util.h"
# include "dotmatrix.h"
# include "dotmatrix_add.h"
# include "dht11.h"
# include "make_matrix.h"
# include "dcht_struct.h"
# include "switch.h"

void			my_setup(unsigned char brightness);
void			error_exit(t_dcht *dcht);
void			display_time(t_dcht *dcht);
void			display_ht(t_dcht *dcht);

#endif
