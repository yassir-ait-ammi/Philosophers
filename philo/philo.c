/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:04:36 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/24 18:10:06 by yaait-am         ###   ########.fr       */
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

void	init_the_args(char **arg, t_data **data, int ac)
{
	(*data)->exit = 0;
	(*data)->nb_philo = ft_atoi(arg[1]);
	(*data)->time_to_die = ft_atoi(arg[2]);
	(*data)->time_to_eat = ft_atoi(arg[3]);
	(*data)->time_to_sleep = ft_atoi(arg[4]);
	if (ac == 6)
		(*data)->nb_of_meals = ft_atoi(arg[5]);
	else
		(*data)->nb_of_meals = -1;
	(*data)->someone_died = 0;
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
		if (i < ac - 1 && is_zero(arg[i]))
			return (NULL);
		i++;
	}
	init_the_args(arg, &data, ac);
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
	if (data->nb_of_meals == 0)
		return (printf("All philo are eating there meals\n"),
			ft_malloc(0, FT_CLEAR), 0);
	if (init_simulation(data) != 0)
		return (ft_malloc(0, FT_CLEAR), 1);
	all_philo_are_alive(data);
	exit_status = data->exit;
	ft_malloc(0, FT_CLEAR);
	return (exit_status);
}
