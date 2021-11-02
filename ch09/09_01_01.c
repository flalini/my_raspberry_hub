/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_01_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:19:58 by ijang             #+#    #+#             */
/*   Updated: 2021/11/02 14:37:20 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wiringPi.h>

#define LED1	1
#define LED2	4

#define SW1		10
#define SW2		11

int	main(void)
{
	int	rcv1, rcv2 = 0;

	if (wiringPiSetup() < 0) {
		exit(0);
	}
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);

	pinMode(SW1, INPUT);
	pinMode(SW2, INPUT);
	while (1) {
		rcv1 = digitalRead(SW1);
		digitalWrite(LED1, rcv1);
		rcv2 = digitalRead(SW2);
		digitalWrite(LED2, rcv2);
	}
	return 0;
}