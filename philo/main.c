/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:46:16 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/05 14:13:45 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_data	*get_struct(void)
{
	static t_data	values;

	return (&values);
}

void	init_struct(t_data *values)
{
	values->live = NULL;
	values->philo = NULL;
	values->fork = NULL;
}

int	only_digit(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	error_arg(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc < 5)
	{
		write(2, "Error: Not enough arguments\n", 28);
		return (1);
	}
	else if (argc > 6)
	{
		write(2, "Error: Too many arguments\n", 26);
		return (1);
	}
	while (i < argc)
	{
		if (!only_digit(argv[i]))
		{
			write(2, "Error: Invalid arguments\n", 25);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*values;
	int		i;

	values = get_struct();
	init_struct(values);
	i = 1;
	if (error_arg(argc, argv))
		return (1);
	values->nb_of_philo = ft_atoi(argv[1]);
	if (values->nb_of_philo < 1)
	{
		write(2, "Error: Invalid arguments\n", 25);
		return (1);
	}
	values->time_to_die = ft_atoi(argv[2]);
	values->time_to_eat = ft_atoi(argv[3]);
	values->time_to_sleep = ft_atoi(argv[4]);
	values->nb_of_times = -2;
	if (argc == 6)
		values->nb_of_times = ft_atoi(argv[5]);
	if (error_int_max(values))
		return (1);
	set_table(values);
	free_n_destroy(values);
	return (0);
}
