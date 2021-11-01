/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:36:24 by ijang             #+#    #+#             */
/*   Updated: 2021/11/01 23:48:40 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdlib.h>
# include <stdio.h>

void	*check_malloc(void **p, size_t size);
void	*check_calloc(void **p, size_t count, size_t size);

#endif