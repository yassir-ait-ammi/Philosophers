/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:03:13 by yaait-am          #+#    #+#             */
/*   Updated: 2025/05/26 09:34:52 by yaait-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# define FT_ALLOC 1
# define FT_CLEAR 0
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>

typedef struct s_data
{
	int				nb_philo;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				nb_of_meals;
	long			start_time;
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*for_dead;
	sem_t			*meals;
	sem_t			*dead;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	sem_t			*alive_sem;
	long			last_meal;
	int				is_alive;
	pid_t			pid;
	t_data			*data;
}	t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}						t_list;

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_strlen(const char *c);
long			ft_atoi(const char *str);
void			*ft_malloc(size_t size, short option);
int				is_nemuric(char *s);
int				init_simulation(t_data *data);
void			print_action(t_philo *philo, const char *msg);
void			ft_usleep(long ms, t_philo *philo);
void			init_semaphore(t_data *data);
void			start_simulation(t_data *data);
long long		get_time_ms(void);
void			clean_exit(t_data *data, int exit_status);
void			*monitor_death(void *arg);
int				if_is_dead(t_philo *philo);
void			wait_and_print_if_all_ate(t_data *data, pid_t *pids);
void			philo_routine(t_philo *philo);
int				is_zero(char *s);
char			*ft_itoa(int n);

#endif
