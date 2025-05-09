/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:04:36 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/09 19:24:41 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *s)
{
	if (!is_nemuric(s))
		return (printf("%s should be just number !!\n", s), 0);
	if (ft_atoi(s) <= 0)
		return (printf("%s should be positive\n", s), 0);
	if (ft_atoi(s) > 2147483647)
		return (printf("%s shouldn't be more than int max\n", s), 0);
	return (1);
}

t_philo	*parsing_the_arg(char **arg, int ac)
{
	int		i;
	t_philo	*philo;

	philo = ft_malloc(sizeof(t_philo), FT_ALLOC);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(arg[i]))
			return (NULL);
		i++;
	}
	philo->nb_philo = ft_atoi(arg[1]);
	philo->tm_to_die = ft_atoi(arg[2]);
	philo->tm_to_eat = ft_atoi(arg[3]);
	philo->tm_to_sleep = ft_atoi(arg[4]);
	if (arg[5])
		philo->nb_of_meals = ft_atoi(arg[5]);
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep>\n");
		ft_malloc(0, FT_CLEAR);
		return (1);
	}
	philo = parsing_the_arg(av, ac);
	if (!philo)
		return (ft_malloc(0, FT_CLEAR), 1);
	ft_malloc(0, FT_CLEAR);
	return (0);
}
