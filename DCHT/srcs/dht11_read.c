/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dht11_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:46:39 by ijang             #+#    #+#             */
/*   Updated: 2021/11/24 19:25:36 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dht11.h"

uint8_t		count_dht11_bit(void)
{
	uint8_t	counter = 0;

	while (digitalRead(DHT11_PIN) == LOW) {
		delayMicroseconds(1);
		if (++counter == 0xFF)
			return 0xFF;
	}

	counter = 0;
	while (digitalRead(DHT11_PIN) == HIGH) {
		delayMicroseconds(1);
		if (++counter == 0xFF)
			return 0xFF;
	}

	return counter;
}

void	dht11_read_val(t_dht11 *dht11)
{
	uint8_t	val[5] = {0, 0, 0, 0, 0};
	uint8_t	counter;
	uint8_t	i = -1;

	pinMode(DHT11_PIN, OUTPUT);
	digitalWrite(DHT11_PIN, HIGH);
	digitalWrite(DHT11_PIN, LOW);
	delay(18);
	digitalWrite(DHT11_PIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHT11_PIN, INPUT);

	count_dht11_bit();

	while (++i < MAX_TIME) {
		counter = count_dht11_bit();
		if (counter == 0xFF)
			return ;
		val[i / 8] <<= 1;
		if (counter > DHT11_SEP)
			val[i / 8] |= 1;
	}

	if (val[4] != ((val[0] + val[1] + val[2] + val[3]) & 0xFF))
		return ;
	if (dht11->data.for_check != *(uint32_t *)val) {
		dht11->data.for_check = *(uint32_t *)val;
		dht11->change = 1;
	}
}

void	dht11_routin(t_dht11 *dht11)
{
	while (1) {
		dht11_read_val(dht11);
		delay(100);
	}
}

int		dht11_thread_start(t_dht11 *dht11, pthread_t *dht11_thread)
{
	dht11_read_val(dht11);
	if (pthread_create(dht11_thread, NULL, (void *)dht11_routin, dht11))
		return -1;
	pthread_detach(*dht11_thread)
	return 0;
}
