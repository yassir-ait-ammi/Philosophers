/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_start_simulation_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:02:45 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/21 19:20:19 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meals");
	sem_unlink("/dead");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philo);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->meals = sem_open("/meals", O_CREAT, 0644, 1);
	data->dead = sem_open("/dead", O_CREAT, 0644, 1);
	if (!data->forks || !data->print || !data->meals || !data->dead)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

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


int init_simulation(t_data *data)
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

void	*monitor_death(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (1)
	{
		sem_wait(&philo->alive_sem);
		int alive = philo->is_alive;
		sem_post(&philo->alive_sem);
		if (!alive)
			break;
		sem_wait(philo->data->meals);
		if ((get_time_ms() - philo->last_meal) > philo->data->tm_to_die)
		{
			sem_wait(philo->data->print);
			printf("%lld %d died\n", get_time_ms() - philo->data->start_time, philo->id);
			exit(1);
		}
		sem_post(philo->data->meals);
		usleep(100);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;
	int			meals_eaten = 0;

	philo->last_meal = get_time_ms();
	sem_init(&philo->alive_sem, 0, 1);
	philo->is_alive = 1;
	pthread_create(&monitor, NULL, monitor_death, philo);
	pthread_detach(monitor);
	while (1)
	{
		print_action(philo, "is thinking");
		sem_wait(philo->data->forks);
		print_action(philo, "has taken a fork");
		sem_wait(philo->data->forks);
		print_action(philo, "has taken a fork");
		sem_wait(philo->data->meals);
		philo->last_meal = get_time_ms();
		sem_post(philo->data->meals);
		print_action(philo, "is eating");
		ft_usleep(philo->data->tm_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		meals_eaten++;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->tm_to_sleep);
		if (philo->data->nb_of_meals != -1 && meals_eaten >= philo->data->nb_of_meals)
		{
			sem_wait(&philo->alive_sem);
			philo->is_alive = 0;
			sem_post(&philo->alive_sem);
			exit(0);
		}
	}
}

void	wait_and_print_if_all_ate(t_data *data, pid_t *pids)
{
	int	status;
	int	exit_count = 0;
	int	i;

	while (exit_count < data->nb_philo)
	{
		if (wait(&status) == -1)
			break;
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				i = 0;
				while (i < data->nb_philo)
				{
					kill(pids[i], SIGKILL);
					i++;
				}
				break;
			}
			else if (WEXITSTATUS(status) == 0)
				exit_count++;
		}
	}
	if (exit_count == data->nb_philo)
		printf("All philosophers have eaten enough meals.\n");
}



void	start_simulation(t_data *data)
{
	int	i;
	pid_t	*pid;

	i = 0;
	data->start_time = get_time_ms();
	pid = ft_malloc(sizeof(pid_t) * data->nb_philo, FT_ALLOC);
	while (i < data->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
		i++;
	}
	wait_and_print_if_all_ate(data, pid);
}
