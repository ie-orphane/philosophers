/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:24:51 by ielyatim          #+#    #+#             */
/*   Updated: 2025/03/09 15:39:22 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*__routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (false)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->rfork);
		printf("%lu %d has taken a fork\n", get_time() - philo->start_time,
			philo->id);
		printf("%lu %d has taken a fork\n", get_time() - philo->start_time,
			philo->id);
		printf("%lu %d is eating\n", get_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		printf("%lu %d is sleeping\n", get_time() - philo->start_time,
			philo->id);
		ft_usleep(philo->time_to_sleep);
		printf("%lu %d is thinking\n", get_time() - philo->start_time,
			philo->id);
	}
	return (NULL);
}

static t_philo	*__philo_init(t_uint id, t_args args, pthread_mutex_t *forks[2])
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	philo->id = id;
	philo->num_of_philos = args.num_of_philos;
	philo->time_to_die = args.time_to_die;
	philo->time_to_eat = args.time_to_eat;
	philo->time_to_sleep = args.time_to_sleep;
	philo->num_of_meals = args.num_of_meals;
	if (philo->id % 2 == 0)
	{
		philo->lfork = forks[0];
		philo->rfork = forks[1];
	}
	else
	{
		philo->lfork = forks[1];
		philo->rfork = forks[0];
	}
	return (philo);
}

t_philo	**philos_init(t_args args, pthread_mutex_t *forks, t_ulong start_time)
{
	t_philo	**philos;
	t_uint	i;

	i = 0;
	philos = ft_calloc(args.num_of_philos * sizeof(t_philo *));
	while (i < args.num_of_philos)
	{
		philos[i] = __philo_init(i, args, (pthread_mutex_t *[]){&forks[i],
				&forks[(i + 1) % args.num_of_philos]});
		philos[i]->start_time = start_time;
		pthread_create(&((philos[i])->trd), NULL, &__routine, philos[i]);
		i++;
	}
	return (philos);
}

void	philos_destroy(t_philo **philos, t_uint num_of_philos)
{
	t_uint	i;

	i = 0;
	while (i < num_of_philos)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}
