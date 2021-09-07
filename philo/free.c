/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 17:21:16 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/05 14:13:57 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	error_int_max(t_data *values)
{
	if (values->nb_of_philo == -1 || values->time_to_die == -1
		|| values->time_to_eat == -1 || values->time_to_sleep == -1
		|| values->nb_of_times == -1)
	{
		write(2, "Error: Invalid arguments\n", 25);
		return (1);
	}
	else if (values->time_to_die == 0 || values->time_to_eat == 0
		|| values->time_to_sleep == 0
		|| values->nb_of_times == 0)
	{
		write(2, "Error: Invalid arguments\n", 25);
		return (1);
	}
	else
		return (0);
}

int	free_n_destroy(t_data *values)
{
	int	i;

	i = 0;
	while (i < values->nb_of_philo)
	{
		pthread_mutex_destroy(&values->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&values->time);
	pthread_mutex_destroy(&values->death);
	pthread_mutex_destroy(&values->write);
	free(values->live);
	free(values->fork);
	free(values->philo);
	return (1);
}
