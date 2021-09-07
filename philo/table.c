/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:14:58 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/04 18:36:53 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	prepare_table(t_data *values)
{
	int	i;

	i = 0;
	values->philo = malloc(sizeof(pthread_t) * values->nb_of_philo);
	values->live = malloc(sizeof(long int) * values->nb_of_philo);
	values->fork = malloc(sizeof(pthread_mutex_t) * values->nb_of_philo);
	if (!values->philo || !values->live || !values->fork)
		return (0);
	memset(values->philo, 0, sizeof(pthread_t) * values->nb_of_philo);
	memset(values->live, 0, sizeof(long int) * values->nb_of_philo);
	memset(values->fork, 0, sizeof(pthread_mutex_t) * values->nb_of_philo);
	while (i < values->nb_of_philo)
	{
		if (pthread_mutex_init(&values->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	wich_fork(t_info *philo, int position, t_data *values)
{
	philo->f_fork = position;
	philo->s_fork = (position + 1) % values->nb_of_philo;
	if (position % 2)
		usleep(100);
	philo->max_meals = values->nb_of_times;
	philo->meal = values->nb_of_times;
	philo->eating = values->time_to_eat;
	philo->sleeping = values->time_to_sleep;
}

int	sit_philos(t_data *values)
{
	int		i;
	t_info	*philo;

	i = 0;
	while (i < values->nb_of_philo)
	{
		philo = malloc(sizeof(t_info));
		if (!philo)
			return (0);
		values->term++;
		memset(philo, 0, sizeof(t_info));
		philo->num = i;
		wich_fork(philo, i, values);
		values->live[i] = values->time_to_die + values->start;
		if (pthread_create(&values->philo[i], NULL, &routine, philo) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	set_table(t_data *values)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&values->write, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&values->death, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&values->time, NULL) != 0)
		return (0);
	if (!prepare_table(values))
		return (0);
	values->dead = 0;
	values->term = 0;
	values->nb_meal = values->nb_of_philo;
	values->start = get_time();
	if (!sit_philos(values))
		return (0);
	check_philos((void *)values);
	return (1);
}
