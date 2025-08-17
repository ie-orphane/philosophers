/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:25:10 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/13 13:25:12 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_meals(t_super *super)
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
			&& super->philos[i].meals_eaten >= super->meals_to_eat)
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

static bool	check_starvation(t_super *super)
{
	int	i;

	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_mutex_lock(&super->meal_lock);
		if (ft_gettime()
			- super->philos[i].last_eaten_time >= super->time_to_die)
		{
			ft_msg(&super->philos[i], "died");
			pthread_mutex_unlock(&super->meal_lock);
			pthread_mutex_lock(&super->dead_lock);
			super->dead_flag = true;
			pthread_mutex_unlock(&super->dead_lock);
			return (true);
		}
		pthread_mutex_unlock(&super->meal_lock);
		i++;
	}
	return (false);
}

void	*super_routine(void *arg)
{
	t_super	*super;

	super = (t_super *)arg;
	while (true)
	{
		if (check_starvation(super) || check_meals(super))
			break ;
		usleep(10);
	}
	return (arg);
}
