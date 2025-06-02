/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:21:05 by ielyatim          #+#    #+#             */
/*   Updated: 2025/06/02 09:21:08 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(int argc, char **argv, t_args *args)
{
	const char	*args_name[] = {"number_of_philosophers", "time_to_die",
		"time_to_eat", "time_to_sleep", "number_of_meals"};
	int			i;

	if (argc < 4 || argc > 5)
	{
		printf("Usage: philo <number_of_philosophers> <time_to_die>"
			" <time_to_eat> <time_to_sleep> [number_of_meals]\n");
		exit(EXIT_FAILURE);
	}
	memset(args, 0, sizeof(t_args));
	i = 0;
	while (i < argc)
	{
		*((unsigned int *)args + i) = ft_uatoi(argv[i]);
		if (*((unsigned int *)args + i) == 0)
		{
			printf(RED "Error:" RESET " invalid argument: " BOLD WHITE);
			printf("%s:" RESET " %s\n", args_name[i], argv[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	unsigned int	i;
	t_philo			**philos;
	pthread_mutex_t	*forks;
	t_super			super;

	parse_args(argc - 1, argv + 1, &args);
	super.start_time = get_time();
	forks = ft_calloc(argc * sizeof(pthread_mutex_t));
	i = args.num_of_philos;
	while (i-- > 0)
		pthread_mutex_init(&forks[i], NULL);
	philos = philos_init(args, forks, super.start_time);
	i = args.num_of_philos;
	while (i-- > 0)
		pthread_join(philos[i]->trd, NULL);
	i = args.num_of_philos;
	while (i-- > 0)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	philos_destroy(philos, args.num_of_philos);
	return (0);
}
