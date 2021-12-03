/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl05_01_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:56:58 by ijang             #+#    #+#             */
/*   Updated: 2021/12/03 13:37:56 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>

#define TRIG 4
#define ECHO 5
#define BUZZ 1

void	getCM(int *distance)
{
	long	time;

	while (1) {
		//Send Trigger Pulse

		digitalWrite(TRIG, HIGH);
		delayMicroseconds(20);
		digitalWrite(TRIG, LOW);

		//Wait for echo start

		while (digitalRead(ECHO) == LOW) {
			continue;
		}

		//Wait for echo end
		time = micros();
		while (digitalRead(ECHO) == HIGH) {
			continue;
		}

		time = micros() - time;

		//Get distance in cm
		*distance = time / 580;
	}
}

void	setup(int *distance, pthread_t *dist_thread)
{
	if (wiringPiSetup() == -1) {
		fprintf(stderr, "Wpi setup failed.\n");
		exit(0);
	}

	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	//TRIG pin must start LOW

	digitalWrite(TRIG, LOW);

	pinMode(BUZZ, OUTPUT);
	digitalWrite(BUZZ, LOW);

	if (pthread_create(dist_thread, NULL, (void *)getCM, distance)) {
		fprintf(stderr, "pthread_create failed.\n");
		exit(0);
	}
	pthread_detach(*dist_thread);

	delay(30);
}

void	beep(int time) {
	digitalWrite(BUZZ, HIGH);
	delay(50);
	digitalWrite(BUZZ, LOW);
	delay(time - 50);
}

int		main(void)
{
	int			distance;
	pthread_t	dist_thread;

	setup(&distance, &dist_thread);

	while (1) {
		switch (distance / 10)
		{
		case 0:
			beep(200);
			break;

		case 1:
			beep(500);
			break;
		
		case 2:
			beep(1000);
			break;
		
		default:
			delay(100);
		}
	}

	return 0;
}