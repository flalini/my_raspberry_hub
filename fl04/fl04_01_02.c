/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl04_01_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:25:53 by ijang             #+#    #+#             */
/*   Updated: 2021/11/23 19:32:55 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wiringPi.h>
#include <stdio.h>
#define CDS		0
#define LED		1
#define PWM		LED

const int pwmValue = 75;

int cdsControl()
{
	int i;
	for (i = 0; i < 10000000; i++) {
		if (digitalRead(CDS) == HIGH)
			pwmWrite(PWM, pwmValue);
		else
			pwmWrite(PWM, 1024 - pwmValue);
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
	pinMode(PWM, PWM_OUTPUT);			/* Set PWM LED as PWM output */
	cdsControl();
	return 0;
}