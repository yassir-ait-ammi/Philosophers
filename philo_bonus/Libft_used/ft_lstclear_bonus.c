/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:29:54 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/09 19:33:35 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*one;
	t_list	*two;

	if (!lst || !del)
		return ;
	one = *lst;
	while (one != NULL)
	{
		two = one->next;
		del(one->content);
		free(one);
		one = two;
	}
	*lst = NULL;
}
