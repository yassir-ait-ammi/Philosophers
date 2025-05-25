/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:02:45 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/25 19:39:59 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_data *data)
{
	int	i;

	data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->nb_philo, FT_ALLOC);
	data->philos = ft_malloc(sizeof(t_philo) * data->nb_philo, FT_ALLOC);
	if (!data->forks || !data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].last_meal = get_time_ms();
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	data->someone_died = 0;
	data->error = 0;
	data->all_ate_enough = 0;
	return (0);
}

int	should_continue(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->state_lock);
	result = (!data->someone_died && !data->all_ate_enough);
	pthread_mutex_unlock(&data->state_lock);
	return (result);
}

void	wait_for_threads(t_data *data, pthread_t monitor, int i)
{
	int	j;

	j = 0;
	if (!data->error)
		pthread_join(monitor, NULL);
	while (j < i)
	{
		pthread_join(data->philos[j].thread, NULL);
		j++;
	}
}

int	all_philo_are_alive(t_data *data)
{
	pthread_t	monitor;
	int			i;

	monitor = 0;
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			data->error = 1337;
			break ;
		}
		i++;
	}
	if (!data->error && pthread_create(&monitor, NULL,
			monitor_routine, data) != 0)
		data->error = 1337;
	wait_for_threads(data, monitor, i);
	return (data->error);
}
