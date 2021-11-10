/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl02_01_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:40:45 by ijang             #+#    #+#             */
/*   Updated: 2021/11/09 23:59:08 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wiringPi.h>

#define LED1	1
#define LED2	4

void state(int delay_t, unsigned short Port1, unsigned short Port2)
{
	digitalWrite(LED1, Port1);
	digitalWrite(LED2, Port2);
	delay(delay_t * 1000);
}

void main(void)
{
	int i = 0;

	if (wiringPiSetup() < 0) {
		exit(0);
	}
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	while (i < 10) {
		state(1, 1, 0);
		state(1, 1, 1);
		state(1, 0, 1);
		state(1, 0, 0);
		i++;
	}
}