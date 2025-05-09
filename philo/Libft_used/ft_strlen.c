/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 08:15:40 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/09 15:21:39 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*y;

	i = 0;
	y = s;
	while (i < n)
	{
		y[i] = c;
		i++;
	}
	return (y);
}
