/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijang <flan101544@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:47:52 by ijang             #+#    #+#             */
/*   Updated: 2021/12/10 18:24:53 by ijang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWITCH_H
# define SWITCH_H

# include "pin.h"
# include <wiringPi.h>
# include <pthread.h>

void		switch_routin(unsigned char *flag);
int			switch_thread_start(unsigned char *flag, pthread_t *switch_thread);

#endif