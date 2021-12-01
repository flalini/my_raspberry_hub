/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl05_01_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:52:30 by ijang             #+#    #+#             */
/*   Updated: 2021/12/01 18:58:45 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define TRUE 1
#define TRIG 4
#define ECHO 5

void	setup(void)
{
	if (wiringPiSetup() == -1) {
		fprintf(stderr, "Wpi setup failed.\n");
		exit(0);
	}

	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	//TRIG pin must start LOW

	digitalWrite(TRIG, LOW);
	delay(30);
}

int		getCM(void)
{
	//Send Trigger Pulse

	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);

	//Wait for echo start

	while (digitalRead(ECHO) == LOW) {
		continue;
	}

	//Wait for echo end
	long startTime = micros();
	while (digitalRead(ECHO) == HIGH) {
		continue;
	}

	long travelTime = micros() - startTime;

	//Get distance in cm
	int distance = travelTime / 58;
	return distance;
}

int		main(void)
{
	setup();

	while (1) {
		int dist = getCM();
		fprintf(stderr, "Distance: %d cm\n", dist);
		delay(1000);
	}

	return 0;
}