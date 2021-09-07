/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:44:00 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/04 15:10:23 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*join;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join = NULL;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join)
	{
		while (s1[i] != '\0')
		{
			join[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
			join[i++] = s2[j++];
		join[i] = '\0';
		return (join);
	}
	return (NULL);
}

char	*timestamp(t_data *values)
{
	long int	stamp;
	char		*time;
	char		*tmp;

	stamp = get_time() - values->start;
	time = ft_itoa(stamp);
	return (time);
}

char	*join_status(t_data *values, int name, char *status)
{
	char		*str;
	char		*tmp;
	char		*num;

	str = timestamp(values);
	tmp = str;
	str = ft_strjoin(str, " Philosopher ");
	free(tmp);
	num = ft_itoa(name + 1);
	tmp = str;
	str = ft_strjoin(str, num);
	free(num);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, " ");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, status);
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, "\n");
	free(tmp);
	tmp = NULL;
	return (str);
}

int	print_status(t_data *values, int philo, char *status, int dead)
{
	char	*str;

	pthread_mutex_lock(&values->write);
	str = join_status(values, philo, status);
	if (check_death(values))
	{
		free(str);
		str = NULL;
		pthread_mutex_unlock(&values->write);
		return (0);
	}
	write(1, str, ft_strlen(str));
	free(str);
	str = NULL;
	if (dead)
	{
		pthread_mutex_lock(&values->death);
		values->dead = 1;
		pthread_mutex_unlock(&values->death);
	}
	pthread_mutex_unlock(&values->write);
	return (1);
}
