/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:13 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/16 10:21:23 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# define FT_ALLOC 1
# define FT_CLEAR 0

typedef struct s_philo
{
	unsigned int		nb_philo;
	unsigned int		tm_to_die;
	unsigned int		tm_to_eat;
	unsigned int		tm_to_sleep;
	unsigned int		nb_of_meals;
}				t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}						t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			*ft_lstnew(void *content);
char			**ft_split(char *str, char *charset);
int				ft_strlen(const char *c);
long			ft_atoi(const char *str);
void			*ft_malloc(size_t size, short option);
int				is_nemuric(char *s);

#endif
