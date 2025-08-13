/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:23:55 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/17 09:08:45 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define BOLD "\033[1m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# define PHILO_MAX 2000

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				num_of_philos;
	bool			is_eating;
	bool			*dead_flag;
	int				meals_eaten;
	int				meals_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_eaten_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
}					t_philo;

typedef struct s_super
{
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	int				num_of_philos;
	int				meals_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	bool			dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
}					t_super;

// -----------------------------------
// utils functions
//
// utils.c
// -----------------------------------

int					ft_atoi(const char *str);
size_t				ft_gettime(void);
void				ft_usleep(size_t time);
bool				ft_isnumeric(const char *str);
void				ft_msg(t_philo *philo, const char *msg);

// -----------------------------------
// init functions
//
// init.c
// -----------------------------------

void				init_super(int argc, char **argv, t_super *super);
void				init_philos(t_super *super);
void				init_threads(t_super *super);

// -----------------------------------
// routine functions
//
// philo.c
// super.c
// -----------------------------------

void				*philo_routine(void *arg);
void				*super_routine(void *arg);

#endif // PHILO_H