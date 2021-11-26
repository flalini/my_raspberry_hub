/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl04_01_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:19:06 by ijang             #+#    #+#             */
/*   Updated: 2021/11/23 19:28:22 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#define CDS 0
#define LED 1

int cdsControl()
{
	int i;
	for (i = 0; i < 10000000; i++) {
		if (digitalRead(CDS) == HIGH) {	/* 빛이감지되면(HIGH) */
			digitalWrite(LED, HIGH);	/* LED On */
			delay(1000);
			digitalWrite(LED, LOW);		/* LED Off */
		}
		delay(10);
	}
	return 0;
}

int main()
{
	if (wiringPiSetup() == -1) {
		fprintf(stderr, "WiringPi setup failed....\n");
		exit(0);
	}
	pinMode(CDS, INPUT);				/* Pin 모드를 입력으로 설정 */
	pinMode(LED, OUTPUT);				/* Pin 모드를 출력으로 설정 */
	cdsControl();
	return 0;
}
