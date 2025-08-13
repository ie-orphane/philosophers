/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:08:45 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/12 20:08:46 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_super(int argc, char **argv, t_super *super)
{
	int	i;

	super->num_of_philos = ft_atoi(argv[1]);
	super->time_to_die = ft_atoi(argv[2]);
	super->time_to_eat = ft_atoi(argv[3]);
	super->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		super->meals_to_eat = ft_atoi(argv[5]);
	else
		super->meals_to_eat = -1;
	super->dead_flag = false;
	pthread_mutex_init(&super->write_lock, NULL);
	pthread_mutex_init(&super->meal_lock, NULL);
	pthread_mutex_init(&super->dead_lock, NULL);
	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_mutex_init(&super->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_super *super)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < super->num_of_philos)
	{
		philo = &super->philos[i];
		philo->id = i + 1;
		philo->num_of_philos = super->num_of_philos;
		philo->time_to_die = super->time_to_die;
		philo->time_to_eat = super->time_to_eat;
		philo->time_to_sleep = super->time_to_sleep;
		philo->meals_to_eat = super->meals_to_eat;
		philo->is_eating = false;
		philo->meals_eaten = 0;
		philo->dead_flag = &super->dead_flag;
		philo->right_fork = &super->forks[(i + 1) % super->num_of_philos];
		philo->left_fork = &super->forks[i];
		philo->start_time = ft_gettime();
		philo->last_eaten_time = philo->start_time;
		philo->write_lock = &super->write_lock;
		philo->meal_lock = &super->meal_lock;
		philo->dead_lock = &super->dead_lock;
		i++;
	}
}

void	init_threads(t_super *super)
{
	int			i;
	pthread_t	super_thread;

	pthread_create(&super_thread, NULL, &super_routine, super);
	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_create(&super->philos[i].thread, NULL, &philo_routine,
			&super->philos[i]);
		i++;
	}
	pthread_join(super_thread, NULL);
	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_join(super->philos[i].thread, NULL);
		i++;
	}
}
