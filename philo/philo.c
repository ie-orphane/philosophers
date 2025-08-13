/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:25:03 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/13 13:25:49 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

static void	eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	ft_msg(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	ft_msg(philo, "has taken a fork");
	philo->is_eating = true;
	ft_msg(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_eaten_time = ft_gettime();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	bool	dead_flag;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (true)
	{
		pthread_mutex_lock(philo->dead_lock);
		dead_flag = *philo->dead_flag;
		pthread_mutex_unlock(philo->dead_lock);
		if (dead_flag)
			break ;
		eating(philo);
		ft_msg(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_msg(philo, "is thinking");
	}
	return (arg);
}
