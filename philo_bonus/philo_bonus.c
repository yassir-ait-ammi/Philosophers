/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:04:36 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/24 09:54:07 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_zero(char *s)
{
	long	num;

	num = ft_atoi(s);
	if (num == 0)
		return (printf("%s : should be more than zero\n", s), 1);
	return (0);
}

int	is_valid_number(char *s)
{
	if (!is_nemuric(s))
		return (printf("%s : should be just number !!\n", s), 0);
	if (ft_atoi(s) < 0)
		return (printf("%s : should be positive\n", s), 0);
	if (ft_atoi(s) > 2147483647)
		return (printf("%s : shouldn't be more than int max\n", s), 0);
	return (1);
}

t_data	*parsing_the_arg(char **arg, int ac)
{
	int		i;
	t_data	*data;

	data = ft_malloc(sizeof(t_data), FT_ALLOC);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(arg[i]))
			return (NULL);
		if (is_zero(arg[i]) && i < ac - 1)
			return (NULL);
		i++;
	}
	data->nb_philo = ft_atoi(arg[1]);
	data->tm_to_die = ft_atoi(arg[2]);
	data->tm_to_eat = ft_atoi(arg[3]);
	data->tm_to_sleep = ft_atoi(arg[4]);
	if (arg[5])
		data->nb_of_meals = ft_atoi(arg[5]);
	else
		data->nb_of_meals = -1;
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		printf("./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep>\n");
		printf("<time_to_sleep> <number_of_meals (optional argument)>\n");
		ft_malloc(0, FT_CLEAR);
		return (1);
	}
	data = parsing_the_arg(av, ac);
	if (!data)
		return (ft_malloc(0, FT_CLEAR), 1);
	if (data->nb_of_meals == 0)
		return (printf("All philo are eating there meals\n"),
			ft_malloc(0, FT_CLEAR), 0);
	init_simulation(data);
	init_semaphore(data);
	start_simulation(data);
	clean_exit(data, EXIT_SUCCESS);
	return (0);
}
