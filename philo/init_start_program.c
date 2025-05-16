/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:02:45 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/16 14:42:47 by yaait-am         ###   ########.fr       */
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
	data->someone_died = 0;
	data->all_ate_enough = 0;
	return (0);
}

void	print_action(t_philo *philo, const char *msg)
{
	long long	now;

	pthread_mutex_lock(&philo->data->print_lock);
	now = get_time_ms() - philo->data->start_time;
	if (!philo->data->someone_died && !philo->data->all_ate_enough)
		printf("Philo %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died && !philo->data->all_ate_enough)
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->meals_lock);
		philo->last_meal = get_time_ms();
		print_action(philo, "is eating");
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meals_lock);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	int full;

	while (!data->someone_died)
	{
		i = 0;
		full = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->meals_lock);
			if ((get_time_ms() - data->philos[i].last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_lock);
				data->someone_died = 1;
				printf("Philo %d is died\n", data->philos[i].id);
				pthread_mutex_unlock(&data->print_lock);
				pthread_mutex_unlock(&data->meals_lock);
				return (NULL);
			}
			if (data->nb_of_meals > 0 && data->philos[i].meals_eaten >= data->nb_of_meals)
				full++;
			pthread_mutex_unlock(&data->meals_lock);
			i++;
		}
		if (data->nb_of_meals > 0 && full == data->nb_philo)
		{
			pthread_mutex_lock(&data->print_lock);
			data->all_ate_enough = 1;
			pthread_mutex_unlock(&data->print_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}


int	all_philo_are_alive(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
			return (perror("Failed to create thread"), 1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (perror("Failed to create monitor"), 1);
	pthread_join(monitor, NULL);

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
