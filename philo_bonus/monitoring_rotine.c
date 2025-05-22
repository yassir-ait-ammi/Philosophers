/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_rotine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:36:06 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/22 15:51:06 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	if_is_dead(t_philo *philo)
{
	int	is_dead;

	sem_wait(philo->data->dead);
	is_dead = philo->data->is_one_dead;
	sem_post(philo->data->dead);
	return (is_dead);
}

int	check_if_one_die(t_philo *philo)
{
	if ((get_time_ms() - philo->last_meal) > philo->data->tm_to_die)
	{
		if (if_is_dead(philo))
			return (1);
		sem_wait(philo->data->dead);
		philo->data->is_one_dead = 1;
		sem_post(philo->data->dead);
		sem_wait(philo->data->print);
		printf("%lld %d died\n", get_time_ms() - philo->data->start_time,
			philo->id);
		sem_post(&philo->alive_sem);
		sem_destroy(&philo->alive_sem);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		alive;

	philo = (t_philo *)arg;
	if (if_is_dead(philo))
		return (NULL);
	while (1)
	{
		if (if_is_dead(philo))
			break ;
		sem_wait(&philo->alive_sem);
		alive = philo->is_alive;
		sem_post(&philo->alive_sem);
		if (!alive)
			break ;
		if (if_is_dead(philo))
			break ;
		sem_wait(philo->data->meals);
		if (check_if_one_die(philo))
			break ;
		sem_post(philo->data->meals);
		usleep(100);
	}
	return (NULL);
}
