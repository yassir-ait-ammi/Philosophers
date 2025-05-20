/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:04:36 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/20 14:57:41 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *s)
{
	long	num;

	if (!is_numeric(s))
		return (printf("%s : should be just number !!\n", s), 0);
	num = ft_atoi(s);
	if (num < 0)
		return (printf("%s : should be positive\n", s), 0);
	if (num > 2147483647)
		return (printf("%s : shouldn't be more than int max\n", s), 0);
	return (1);
}

t_data	*parsing_the_arg(char **arg, int ac)
{
	t_data	*data;
	int		i;

	data = ft_malloc(sizeof(t_data), FT_ALLOC);
	if (!data)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(arg[i]))
			return (NULL);
		i++;
	}
	data->exit = 0;
	data->nb_philo = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	data->nb_of_meals = (ac == 6) ? ft_atoi(arg[5]) : -1;
	data->someone_died = 0;
	if (data->nb_philo == 1)
	{
		printf("Philosopher 1 died\n");
		return (NULL);
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		exit_status;

	if (ac != 5 && ac != 6)
	{
		printf("./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> ");
		printf("<time_to_sleep> <number_of_meals (optional argument)>\n");
		ft_malloc(0, FT_CLEAR);
		return (1);
	}
	data = parsing_the_arg(av, ac);
	if (!data)
		return (ft_malloc(0, FT_CLEAR), 1);
	if (!data->nb_of_meals)
		return (ft_malloc(0, FT_CLEAR), 0);
	if (init_simulation(data) != 0)
		return (ft_malloc(0, FT_CLEAR), 1);
	all_philo_are_alive(data);
	exit_status = data->exit;
	ft_malloc(0, FT_CLEAR);
	return (exit_status);
}
