/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:02:45 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/26 09:33:06 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_simulation(t_data *data)
{
	int	i;

	data->philos = ft_malloc(sizeof(t_philo) * data->nb_philo, FT_ALLOC);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].pid = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

void	clean_exit(t_data *data, int exit_status)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print)
		sem_close(data->print);
	if (data->meals)
		sem_close(data->meals);
	if (data->dead)
		sem_close(data->dead);
	if (data->for_dead)
		sem_close(data->for_dead);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals");
	sem_unlink("/dead");
	sem_unlink("/for_dead");
	ft_malloc(0, FT_CLEAR);
	exit(exit_status);
}

void	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals");
	sem_unlink("/dead");
	sem_unlink("/for_dead");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->meals = sem_open("/meals", O_CREAT, 0644, 1);
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	data->for_dead = sem_open("/for_dead", O_CREAT, 0644, 1);
	if (!data->forks || !data->print || !data->meals
		|| !data->dead || !data->for_dead)
	{
		printf("sem_open failed\n");
		clean_exit(data, EXIT_FAILURE);
	}
}
