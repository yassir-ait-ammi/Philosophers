/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_rotine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:36:06 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/25 19:00:30 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	if_is_dead(t_philo *philo)
{
	int	is_dead;

	sem_wait(philo->data->for_dead);
	is_dead = philo->data->dead->__align;
	sem_post(philo->data->for_dead);
	return (is_dead);
}

int	check_if_one_die(t_philo *philo)
{
	if ((get_time_ms() - philo->last_meal) >= philo->data->tm_to_die)
	{
		if (!if_is_dead(philo))
			return (1);
		sem_wait(philo->data->for_dead);
		philo->data->dead->__align = 0;
		sem_post(philo->data->for_dead);
		sem_wait(philo->data->print);
		printf("%lld %d died\n", get_time_ms() - philo->data->start_time,
			philo->id);
		sem_post(philo->data->print);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		alive;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!if_is_dead(philo))
			break ;
		sem_wait(philo->alive_sem);
		alive = philo->is_alive;
		sem_post(philo->alive_sem);
		if (!alive)
			break ;
		if (!if_is_dead(philo))
			break ;
		sem_wait(philo->data->meals);
		if (check_if_one_die(philo))
		{
			sem_post(philo->data->meals);
			break ;
		}
		sem_post(philo->data->meals);
		usleep(1000);
	}
	return (NULL);
}
