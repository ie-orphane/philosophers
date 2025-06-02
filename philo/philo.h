/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:23:55 by ielyatim          #+#    #+#             */
/*   Updated: 2025/03/09 15:38:05 by ielyatim         ###   ########.fr       */
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
# define BOLD "\033[1m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_args
{
	t_uint				num_of_philos;
	t_uint				time_to_die;
	t_uint				time_to_eat;
	t_uint				time_to_sleep;
	t_uint				num_of_meals;
}						t_args;

typedef struct s_super
{
	pthread_mutex_t		write;
	bool				dead;
	t_ulong				start_time;
}						t_super;

typedef struct s_philo
{
	t_uint				id;
	t_uint				num_of_philos;
	t_uint				time_to_die;
	t_uint				time_to_eat;
	t_uint				time_to_sleep;
	t_uint				num_of_meals;
	t_ulong				start_time;
	pthread_t			trd;
	pthread_mutex_t		*write;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
}						t_philo;

/* ************************************* */
/*                utils                  */
/* ************************************* */
t_uint					ft_uatoi(const char *str);
t_ulong					get_time(void);
void					ft_usleep(t_ulong time);
void					*ft_calloc(size_t size);

/* ************************************* */
/*                philo                  */
/* ************************************* */
t_philo					**philos_init(t_args args, pthread_mutex_t *forks,
							t_ulong start_time);
void					philos_destroy(t_philo **philos, t_uint num_of_philos);

#endif // PHILO_H