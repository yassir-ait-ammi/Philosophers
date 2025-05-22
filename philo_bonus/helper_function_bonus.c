/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:44:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/22 16:33:33 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_number(char c)
{
	return ('0' <= c && c <= '9');
}

int	is_nemuric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!is_number(s[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, const char *msg)
{
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", get_time_ms() - philo->data->start_time,
		philo->id, msg);
	sem_post(philo->data->print);
}

void	ft_usleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
	{
		if (if_is_dead(philo))
			break ;
		usleep(100);
	}
}
