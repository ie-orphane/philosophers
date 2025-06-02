/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:14:30 by ielyatim          #+#    #+#             */
/*   Updated: 2025/06/02 08:14:41 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts a string to an unsigned integer.
 *
 * @param str The string to convert.
 * @return The converted unsigned integer, or 0 if the string is invalid.
 *
 * This function checks if the string is a valid
 * representation of an unsigned integer.
 *
 * It returns 0 if the string is NULL, empty, or contains non-digit characters.
 * It also checks for overflow, returning 0 if the result exceeds UINT_MAX.
 */
unsigned int	ft_uatoi(const char *str)
{
	unsigned int	num;
	int				i;

	if (!str || !*str)
		return (0);
	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		num = num * 10 + (str[i] - '0');
		if (num > UINT_MAX)
			return (0);
		i++;
	}
	return (num);
}

t_ulong	get_time(void)
{
	struct timeval	tv;
	t_ulong			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(t_ulong time)
{
	t_ulong	start;
	t_ulong	current;

	start = get_time();
	while (true)
	{
		current = get_time();
		if (current - start >= time)
			break ;
	}
}

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf(RED "Error:" RESET " memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	memset(ptr, 0, size);
	return (ptr);
}
