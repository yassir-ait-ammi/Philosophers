/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:48:23 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/25 18:56:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_count(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb / 10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*yas;
	long	nb;

	nb = n;
	i = ft_count(nb);
	yas = ft_malloc ((i + 1) * sizeof(char), FT_ALLOC);
	if (!yas)
		return (NULL);
	yas[i] = '\0';
	if (nb < 0)
	{
		yas[0] = '-';
		nb = -nb;
	}
	i = i - 1;
	if (nb == 0)
		yas[i] = '0';
	while (nb > 0)
	{
		yas[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (yas);
}
