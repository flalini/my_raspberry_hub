/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 00:10:19 by ijang             #+#    #+#             */
/*   Updated: 2021/11/02 00:46:45 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>

void	test_while(void)
{
	int	sum = 0, i = -1;

	while (++i < 100000)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
	i = -1;
	while (++i < 50000)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
	while (++i <= 100000)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
}

void	test_for(void)
{ 
	int	sum = 0;

	for (int i = 0; i < 100000; ++i)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
	for (int i = 0; i < 50000; ++i)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
	for (int i = 0; i < 50000; ++i)
		for (int j = 0; j < 10000;)
			sum += i * ++j;
}

int		main(void)
{
	clock_t	start, end;

	test_for();
	test_while();

	start = clock();
	test_for();
	end = clock();
	printf("for   : %f\n", (double)(end - start));
	start = clock();
	test_while();
	end = clock();
	printf("while : %f\n", (double)(end - start));
	start = clock();
	test_for();
	end = clock();
	printf("for   : %f\n", (double)(end - start));
	start = clock();
	test_while();
	end = clock();
	printf("while : %f\n", (double)(end - start));
	start = clock();
	test_for();
	end = clock();
	printf("for   : %f\n", (double)(end - start));
	start = clock();
	test_while();
	end = clock();
	printf("while : %f\n", (double)(end - start));
	start = clock();
	test_for();
	end = clock();
	printf("for   : %f\n", (double)(end - start));
	start = clock();
	test_while();
	end = clock();
	printf("while : %f\n", (double)(end - start));
	return (0);
}