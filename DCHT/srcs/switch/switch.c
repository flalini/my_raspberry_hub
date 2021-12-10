/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:02:49 by ijang             #+#    #+#             */
/*   Updated: 2021/12/11 00:16:23 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "switch.h"

void		switch_routin(unsigned char *flag)
{
	*flag = 0;
	while (1) {
		if (!digitalRead(SW_PIN)) {
			*flag = 1;
			delay(10);
			while (!digitalRead(SW_PIN)) {
				delay(10);
			} 
		}
	}
}

int			switch_thread_start(unsigned char *flag, pthread_t *switch_thread)
{
	if (pthread_create(switch_thread, NULL, (void *)switch_routin, flag))
		return -1;
	pthread_detach(*switch_thread);
	return 0;
}