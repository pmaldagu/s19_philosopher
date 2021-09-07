/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:42:05 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/05 13:50:14 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num;
	int				f_fork;
	int				s_fork;
	int				meal;
	int				max_meals;
	int				eating;
	int				sleeping;
}					t_info;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times;
	int				dead;
	int				nb_meal;
	int				term;
	long int		*live;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	time;
	pthread_mutex_t	write;
	long int		start;
}					t_data;

/*
** Main
*/

t_data				*get_struct(void);

/*
** Table
*/

int					prepare_table(t_data *values);
void				wich_fork(t_info *philo, int position, t_data *values);
int					sit_philos(t_data *values);
int					set_table(t_data *values);

/*
** Write
*/

char				*ft_strjoin(char *s1, char *s2);
char				*join_statut(t_data *values, int name, char *status);
char				*timestamp(t_data *values);
int					print_status(t_data *values, int philo,
						char *status, int dead);

/*
** Diner
*/

int					is_sleeping(t_info *philo, t_data *values);
int					is_eating(t_info *philo, t_data *values);
int					is_thinking(t_info *philo, t_data *values);
void				*routine(void *arg);

/*
** Clock
*/

int					interrupt_time(int time);
long int			get_time(void);

/*
** Status
*/

int					philo_died(t_data *values, int philo);
int					check_death(t_data *values);
void				*check_philos(void *arg);

/*
** Utils
*/

int					ft_strlen(char *str);
int					ft_atoi(const char *str);
int					only_digit(char *str);
int					ft_charsize_int(int n);
char				*ft_itoa(int n);

/*
** free
*/

int					error_int_max(t_data *values);
int					free_n_destroy(t_data *values);

#endif
