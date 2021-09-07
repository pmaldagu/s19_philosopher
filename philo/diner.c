/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:36:43 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/05 14:59:08 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	is_sleeping(t_info *philo, t_data *values)
{
	if (philo->max_meals > 0)
		philo->meal--;
	if (philo->meal == 0)
	{
		pthread_mutex_lock(&values->time);
		values->nb_meal--;
		pthread_mutex_unlock(&values->time);
	}
	pthread_mutex_unlock(&values->fork[philo->f_fork]);
	pthread_mutex_unlock(&values->fork[philo->s_fork]);
	if (!print_status(values, philo->num, "is sleeping", 0))
		return (0);
	interrupt_time(philo->sleeping);
	return (1);
}

int	is_eating(t_info *philo, t_data *values)
{
	if (!print_status(values, philo->num, "is eating", 0))
		return (0);
	pthread_mutex_lock(&values->time);
	values->live[philo->num] = get_time() + values->time_to_die;
	pthread_mutex_unlock(&values->time);
	interrupt_time(philo->eating);
	return (1);
}

int	is_thinking(t_info *philo, t_data *values)
{
	if (!print_status(values, philo->num, "is thinking", 0))
		return (0);
	pthread_mutex_lock(&values->fork[philo->f_fork]);
	if (!print_status(values, philo->num, "has taken a fork", 0)
		|| values->nb_of_philo == 1)
	{
		pthread_mutex_unlock(&values->fork[philo->f_fork]);
		return (0);
	}
	pthread_mutex_lock(&values->fork[philo->s_fork]);
	if (!print_status(values, philo->num, "has taken a fork", 0))
	{
		pthread_mutex_unlock(&values->fork[philo->f_fork]);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_info	*phil;
	t_data	*values;
	int		swap;

	values = get_struct();
	phil = (t_info *)arg;
	while (1)
	{
		if (!is_thinking(phil, values))
			break ;
		if (!is_eating(phil, values))
			break ;
		if (!is_sleeping(phil, values))
			break ;
	}
	free(phil);
	pthread_mutex_lock(&values->death);
	values->term--;
	pthread_mutex_unlock(&values->death);
	return ((void *)1);
}
