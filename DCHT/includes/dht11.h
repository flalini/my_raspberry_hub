/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dht11.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:14:20 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 13:51:30 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DHT11_H
# define DHT11_H

# include <wiringPi.h>
# include <stdint.h>
# include <pthread.h>
# include "pin.h"

# define MAX_TIME	40
# define DHT11_SEP	20

typedef union	u_dht11_val
{
	uint8_t		val[4];
	uint32_t	for_check;
}				t_dht11_val;

typedef struct	s_dht11
{
	t_dht11_val	data;
	uint8_t		change;
}				t_dht11;

uint8_t		count_dht11_bit(void);
void		dht11_read_val(t_dht11 *dht11);
void		dht11_routin(t_dht11 *dht11);
int			dht11_thread_start(t_dht11 *dht11, pthread_t *dht11_thread);

#endif
