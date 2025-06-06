/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:44:26 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/25 19:35:34 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char c)
{
	return ('0' <= c && c <= '9');
}

int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!is_number(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_zero(char *s)
{
	long	num;

	num = ft_atoi(s);
	if (num == 0)
		return (printf("%s : should be more than zero\n", s), 1);
	return (0);
}
