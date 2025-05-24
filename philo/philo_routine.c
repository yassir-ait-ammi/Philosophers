/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:47:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/24 10:43:17 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->nb_philo;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}
	print_action(philo, "is taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*if_eat_or_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_lock);
	if (philo->data->someone_died || philo->data->all_ate_enough)
	{
		pthread_mutex_unlock(&philo->data->state_lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->state_lock);
	return ((void *)1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meals_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->meals_lock);
	while (1)
	{
		if (!if_eat_or_die(philo))
			break ;
		print_action(philo, "is thinking");
		pick_forks(philo);
		pthread_mutex_lock(&philo->data->meals_lock);
		philo->last_meal = get_time_ms();
		philo->meals_eaten++;
		if (philo->meals_eaten > 2147483647)
			break ;
		pthread_mutex_unlock(&philo->data->meals_lock);
		print_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat, philo);
		release_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo);
	}
	return (NULL);
}
