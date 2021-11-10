/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl02_04_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:00:58 by ijang             #+#    #+#             */
/*   Updated: 2021/11/10 00:01:56 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define LED1	1
#define LED2	4

#define PWM		LED1

#define SW1		10

const int pwmValue = 75;					// LED brightness

int main(void)
{
	if (wiringPiSetup() < 0) {
		exit(0);
	}
	pinMode(PWM, PWM_OUTPUT);				// Set PWM LED as PWM output
	pinMode(LED2, OUTPUT);					// Set regular LED as output
	pinMode(SW1, INPUT);					// Set button as INPUT
	pullUpDnControl(SW1, PUD_UP);			// Enable pull-up resistor on button
	printf("Blinker is running! Press CTRL+C to quit.\n");
	while (1) {
		if (digitalRead(SW1)) {				// button release
			pwmWrite(PWM, pwmValue);		// PWM LED at bright setting
			digitalWrite(LED2, LOW);		// Regular LED off
		} else {							// button is pressed
			pwmWrite(PWM, 1024 - pwmValue);	// PWM LED at dim setting
			digitalWrite(LED2, HIGH);		// Turn LED ON
			delay(100);						// Wait 100ms
			digitalWrite(LED2, LOW);		// Turn LED OFF
			delay(100);						// Wait 100ms again
		}
	}
}