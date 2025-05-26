/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_wait_andwork_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:30:37 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/26 13:40:51 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_for_parent(int exit_count, t_data *data)
{
	if (exit_count == data->nb_philo)
	{
		printf("All philosophers have eaten enough meals.\n");
		clean_exit(data, EXIT_SUCCESS);
	}
	else
		clean_exit(data, EXIT_FAILURE);
}

void	wait_and_print_if_all_ate(t_data *data, pid_t *pids)
{
	int (status), (exit_count);
	(void)pids;
	exit_count = 0;
	while (exit_count < data->nb_philo)
	{
		if (wait(&status) == -1)
			break ;
		if (WEXITSTATUS(status) == 0)
			exit_count++;
	}
	exit_for_parent(exit_count, data);
}

void	start_simulation(t_data *data)
{
	int		i;
	pid_t	*pid;

	i = 0;
	data->start_time = get_time_ms();
	pid = ft_malloc(sizeof(pid_t *) * data->nb_philo, FT_ALLOC);
	while (i < data->nb_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("failed to creat more proccesse\n");
			break ;
		}
		if (pid[i] == 0)
		{
			philo_routine(&data->philos[i]);
			clean_exit(data, EXIT_SUCCESS);
		}
		i++;
	}
	wait_and_print_if_all_ate(data, pid);
}
