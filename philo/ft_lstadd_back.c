/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:57:50 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/24 19:29:19 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*yas;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		yas = *lst;
		while (yas->next != NULL)
			yas = yas->next;
		yas->next = new;
	}
}
