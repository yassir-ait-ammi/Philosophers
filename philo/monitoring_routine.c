/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:48:09 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/17 11:09:36 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_data			*data;
	int				i;
	int				full;
	int				should_stop;
	long long		current_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		full = 0;
		should_stop = 0;
		while (i < data->nb_philo && !should_stop)
		{
			current_time = get_time_ms();
			pthread_mutex_lock(&data->meals_lock);
			if ((current_time - data->philos[i].last_meal) > data->time_to_die)
			{
				pthread_mutex_unlock(&data->meals_lock);
				pthread_mutex_lock(&data->state_lock);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->state_lock);
				pthread_mutex_lock(&data->print_lock);
				printf("%lld Philo %d died\n",
					current_time - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			if (data->nb_of_meals > 0
				&& data->philos[i].meals_eaten >= data->nb_of_meals)
				full++;
			pthread_mutex_unlock(&data->meals_lock);
			i++;
		}
		if (data->nb_of_meals > 0 && full == data->nb_philo)
		{
			pthread_mutex_lock(&data->state_lock);
			data->all_ate_enough = 1;
			pthread_mutex_unlock(&data->state_lock);
			return (NULL);
		}
		pthread_mutex_lock(&data->state_lock);
		should_stop = data->someone_died;
		pthread_mutex_unlock(&data->state_lock);
		if (should_stop)
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	print_action(t_philo *philo, const char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->data->print_lock);
	if (should_continue(philo->data))
	{
		now = get_time_ms() - philo->data->start_time;
		printf("%lld Philo %d %s\n", now, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}
