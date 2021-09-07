/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:28:33 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/04 14:11:32 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	interrupt_time(int time)
{
	int				i;
	long int		timer;

	i = 0;
	timer = get_time();
	while (1)
	{
		if ((get_time() - timer) >= time)
			break ;
		usleep(500);
	}
	return (1);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
