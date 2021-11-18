#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TIME	40
#define DHT11		7

unsigned char	count_dht11_bit()
{
	unsigned char	counter = 0;

	while (digitalRead(DHT11) == LOW) {
		delayMicroseconds(1);
		if (++counter == 0xFF)
			return 0xFF;
	}

	counter = 0;
	while (digitalRead(DHT11) == HIGH) {
		delayMicroseconds(1);
		if (++counter == 0xFF)
			return 0xFF;
	}

	return counter;
}

unsigned int	dht11_read_val()
{
	unsigned char	val[5] = {0, 0, 0, 0, 0};
	unsigned char	temp[40];
	unsigned char	counter;
	unsigned char	i = -1;

	pinMode(DHT11, OUTPUT);
	digitalWrite(DHT11, HIGH);
	digitalWrite(DHT11, LOW);
	delay(18);
	digitalWrite(DHT11, HIGH);
	delayMicroseconds(30);
	pinMode(DHT11, INPUT);

	count_dht11_bit();

	while (++i < MAX_TIME) {
		counter = count_dht11_bit();
		if (counter == 255)
			return -1;
		temp[i] = counter;
		val[i / 8] <<= 1;
		if (counter > 20)
			val[i / 8] |= 1;
	}

	if (val[4] != ((val[0] + val[1] + val[2] + val[3]) & 0xFF))
		return -1;
	i = -1;
	while (++i < 40)
		printf("[%hhu]\n", temp[i]);
	printf("\n");
	return *(unsigned int *)(&val);
}

int main(void)
{
	unsigned int	vali;
	unsigned char	*valc;
	float			fahrenheit;

	if (wiringPiSetup() == -1)
		exit(1);

	printf("Interfacing Temperature and Humidity Sensor (DHT11) With Raspberry Pi\n");
	valc = (unsigned char *)(&vali);

	for (int i = 0; i < 30; ++i) {
		vali = dht11_read_val();
		if (vali == 0xFFFFFFFF)
			printf("Invalid Data!!\n");
		else {
			fahrenheit = valc[2] * 9.0 / 5.0 + 32.0;
			printf("Humidity = %hhu.%hhu %% Temperature = %hhu.%hhu *C (%.1f *F)\n", valc[0], valc[1], valc[2], valc[3], fahrenheit);
		}
		delay(1000);
	}
	return 0;
}