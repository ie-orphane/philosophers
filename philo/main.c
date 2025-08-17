/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:21:05 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/17 09:17:32 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_err(const char *msg)
{
	write(2, msg, strlen(msg));
}

static bool	ft_parse(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_err(RED "Error:" RESET " Invalid number of arguments.\n");
		ft_err(YELLOW "\nUsage:" RESET "\n  philo <num_of_philos> <time");
		ft_err("_to_die> <time_to_eat> <time_to_sleep> [num_of_meals]\n");
		return (true);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_isnumeric(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			ft_err(RED "Error:" RESET " Invalid argument: " BOLD WHITE);
			ft_err(argv[i]);
			ft_err(RESET "\n");
			return (true);
		}
		i++;
	}
	return (false);
}

void	ft_destroy(t_super *super)
{
	int	i;

	pthread_mutex_destroy(&super->write_lock);
	pthread_mutex_destroy(&super->meal_lock);
	pthread_mutex_destroy(&super->dead_lock);
	i = 0;
	while (i < super->num_of_philos)
	{
		pthread_mutex_destroy(&super->forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_super	super;

	if (ft_parse(argc, argv))
		return (1);
	init_super(argc, argv, &super);
	init_philos(&super);
	init_threads(&super);
	ft_destroy(&super);
	return (0);
}
