/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl02_02_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:00:54 by ijang             #+#    #+#             */
/*   Updated: 2021/11/10 00:05:31 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wiringPi.h>

#define LED1	1
#define LED2	4

#define SW1		10

void DisplayState(int state)
{
	switch (state) {
		case 1:
			digitalWrite(LED1, 1);
			digitalWrite(LED2, 0);
			break;
		case 2:
			digitalWrite(LED1, 0);
			digitalWrite(LED2, 1);
			break;
		case 3:
			digitalWrite(LED1, 1);
			digitalWrite(LED2, 1);
			break;
		case 4:
			digitalWrite(LED1, 0);
			digitalWrite(LED2, 0);
		default:
			break;
	}
}

void main(void)
{
	int state = 0;
	int i = 0;
	
	if(wiringPiSetup() < 0) {
		exit(0);
	}
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(SW1, INPUT);
	state = 1;
	while (state <= 4) {
		DisplayState(state);
		while (1) {
			if (digitalRead(SW1) == 0) {
				break;
			}
		}
		while (1) {
			if (digitalRead(SW1) == 1) {
				break;
			}
		}
		state++;
	}
	DisplayState(1);
}