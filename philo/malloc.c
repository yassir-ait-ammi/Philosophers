/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:33:12 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/26 09:39:28 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*mem_alloc(size_t size)
{
	t_list	*new;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		return (NULL);
	}
	new = ft_lstnew(ptr);
	if (!new)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		return (NULL);
	}
	return (new);
}

void	*ft_malloc(size_t size, short option)
{
	static t_list	*head;
	t_list			*new;

	if (option == FT_ALLOC)
	{
		new = mem_alloc(size);
		if (!new)
		{
			ft_lstclear(&head, free);
			printf("Memory allocation failed\n");
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		return (new->content);
	}
	if (option == FT_CLEAR)
		ft_lstclear(&head, free);
	return (NULL);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philo *philo)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		if (!if_eat_or_die(philo))
			break ;
		usleep(100);
	}
}
