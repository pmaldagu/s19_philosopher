/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:39:51 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/05 14:58:30 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	philo_died(t_data *values, int philo)
{
	pthread_mutex_lock(&values->time);
	if (get_time() >= values->live[philo] && values->live[philo])
	{
		print_status(values, philo, "died", 1);
		pthread_mutex_unlock(&values->time);
		return (1);
	}
	else if (!values->nb_meal)
	{
		pthread_mutex_unlock(&values->time);
		return (1);
	}
	pthread_mutex_unlock(&values->time);
	return (0);
}

int	check_death(t_data *values)
{
	pthread_mutex_lock(&values->death);
	if (values->dead)
	{
		pthread_mutex_unlock(&values->death);
		return (1);
	}
	pthread_mutex_unlock(&values->death);
	return (0);
}

void	*check_philos(void *arg)
{
	int		i;
	t_data	*values;

	values = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < values->nb_of_philo)
		{
			if (philo_died(values, i))
			{
				pthread_mutex_lock(&values->death);
				values->dead = 1;
				pthread_mutex_unlock(&values->death);
				while (values->term != 0)
					usleep(4000);
				return ((void *)1);
			}
			i++;
		}
		usleep(4000);
	}
	return ((void *)0);
}
