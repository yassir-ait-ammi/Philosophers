/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:13 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/16 10:41:37 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define FT_ALLOC 1
# define FT_CLEAR 0

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;

	int				someone_died;
	int				all_ate_enough;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
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
int				all_philo_are_alive(t_data *data);
int				is_numeric(char *s);
int				init_simulation(t_data *data);
long long		get_time_ms(void);
void			ft_usleep(int ms);

#endif
