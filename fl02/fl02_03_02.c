/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl02_03_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 14:56:52 by ijang             #+#    #+#             */
/*   Updated: 2021/11/13 14:58:23 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LED1	1

void pwm(double on, double off)
{
	for (int n = 0; n < 10; n++) {
	digitalWrite(LED1, 1);
	delay(on * 100);
	digitalWrite(LED1, 0);
	delay(off * 100);
	}
}

void main(void)
{
	double sub = 0.0;

	if (wiringPiSetup() < 0) {
		exit(0);
	}
	pinMode(LED1, OUTPUT);
	for (int i = 0; i < 7; i++) {
		printf("%d\n", i);
		sub = i * 0.25;
		pwm(2.0 - sub, 1.0);
	}
}