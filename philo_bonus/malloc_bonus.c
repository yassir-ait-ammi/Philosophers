/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:33:12 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/21 15:46:54 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_list	*mem_alloc(size_t size)
{
	t_list	*new;
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new = ft_lstnew(ptr);
	if (!new)
	{
		ft_malloc(0, FT_CLEAR);
		free(ptr);
		exit(EXIT_FAILURE);
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
			printf("allocation fail\n");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&head, new);
		return (new->content);
	}
	if (option == FT_CLEAR)
		ft_lstclear(&head, free);
	return (NULL);
}
