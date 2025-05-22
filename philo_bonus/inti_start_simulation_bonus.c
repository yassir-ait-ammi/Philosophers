/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_start_simulation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:02:45 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/22 15:57:02 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->tm_to_eat / 2);
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	print_the_action(t_philo *philo, int *meals_eaten)
{
	if (if_is_dead(philo))
		return (1);
	print_action(philo, "is thinking");
	if (philo->data->nb_philo % 2 != 0)
		ft_usleep(philo->data->tm_to_eat / 2);
	if (if_is_dead(philo))
		return (1);
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	if (if_is_dead(philo))
		return (1);
	sem_wait(philo->data->forks);
	if (if_is_dead(philo))
		return (1);
	sem_wait(philo->data->meals);
	philo->last_meal = get_time_ms();
	sem_post(philo->data->meals);
	print_action(philo, "is eating");
	ft_usleep(philo->data->tm_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	(*meals_eaten)++;
	print_action(philo, "is sleeping");
	return (0);
}

int	check_if_meals(t_philo *philo, int meals_eaten)
{
	if (philo->data->nb_of_meals != -1
		&& meals_eaten >= philo->data->nb_of_meals)
	{
		if (if_is_dead(philo))
			return (1);
		sem_wait(&philo->alive_sem);
		philo->is_alive = 0;
		sem_post(&philo->alive_sem);
		sem_destroy(&philo->alive_sem);
		return (1);
	}
	return (0);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;
	int			meals_eaten;

	meals_eaten = 0;
	philo->last_meal = get_time_ms();
	sem_init(&philo->alive_sem, 0, 1);
	philo->is_alive = 1;
	pthread_create(&monitor, NULL, monitor_death, philo);
	while (1)
	{
		if (print_the_action(philo, &meals_eaten))
			break ;
		ft_usleep(philo->data->tm_to_sleep);
		if (check_if_meals(philo, meals_eaten))
			break ;
	}
	pthread_join(monitor, NULL);
	if (philo->data->nb_of_meals != -1
		&& meals_eaten >= philo->data->nb_of_meals)
		clean_exit(philo->data, EXIT_SUCCESS);
	else
		clean_exit(philo->data, EXIT_FAILURE);
}
