/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:29:57 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/13 09:29:58 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	bool	dead_flag;

	pthread_mutex_lock(philo->dead_lock);
	dead_flag = *philo->dead_flag;
	pthread_mutex_unlock(philo->dead_lock);
	return (dead_flag);
}

void	ft_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!is_dead(philo))
		printf("%zu %d %s\n", ft_gettime() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	assign_forks(t_philo *philo, pthread_mutex_t **first_fork,
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

void	eating(t_philo *philo)
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

	philo = (t_philo *)arg;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(1);
	while (!is_dead(philo))
	{
		eating(philo);
		ft_msg(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_msg(philo, "is thinking");
	}
	return (arg);
}

bool	check_meals(t_super *super)
{
	int	philo_ate;
	int	i;

	if (super->meals_to_eat < 0)
		return (false);
	philo_ate = 0;
	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_mutex_lock(&super->meal_lock);
		if (!super->philos[i].is_eating
			&& super->philos[i].meals_eaten == super->meals_to_eat)
			philo_ate++;
		pthread_mutex_unlock(&super->meal_lock);
		i++;
	}
	if (philo_ate == super->num_of_philos)
	{
		pthread_mutex_lock(&super->dead_lock);
		super->dead_flag = true;
		pthread_mutex_unlock(&super->dead_lock);
		return (true);
	}
	return (false);
}

void	*super_routine(void *arg)
{
	t_super	*super;

	super = (t_super *)arg;
	while (true)
	{
		if (check_meals(super))
			break ;
	}
	return (arg);
}
