/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:47:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/21 20:03:58 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
		if (philo->data->nb_philo == 3)
			ft_usleep(philo->data->time_to_eat / 2);
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
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
		pthread_mutex_unlock(&philo->data->meals_lock);
		print_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		release_forks(philo);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
