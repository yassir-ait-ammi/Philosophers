/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:47:20 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/17 11:06:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_for_philo_routine(t_philo **p, pthread_mutex_t **f
		, pthread_mutex_t **s)
{
	if ((*p)->id % 2 == 0)
		usleep(1000);
	if ((*p)->id % (*p)->data->nb_philo
		< (((*p)->id + 1) % (*p)->data->nb_philo))
	{
		*f = (*p)->left_fork;
		*s = (*p)->right_fork;
	}
	else
	{
		*f = (*p)->right_fork;
		*s = (*p)->left_fork;
	}
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philo *)arg;
	init_for_philo_routine(&philo, &first_fork, &second_fork);
	while (1)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo->data->someone_died || philo->data->all_ate_enough)
		{
			pthread_mutex_unlock(&philo->data->print_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		print_action(philo, "is thinking");
		pthread_mutex_lock(first_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(second_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->meals_lock);
		philo->last_meal = get_time_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meals_lock);
		print_action(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}
