/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 23:40:17 by ijang             #+#    #+#             */
/*   Updated: 2021/11/01 23:52:56 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	*check_malloc(void **p, size_t size)
{
	*p = malloc(size);
	return *p;
}

void	*check_calloc(void **p, size_t count, size_t size)
{
	*p = calloc(count, size);
	return *p;
}