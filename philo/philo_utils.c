/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 21:24:22 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/24 21:27:45 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time_in_ms(void)
{
	struct timeval	t;	

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

uint64_t	elapsed_time(uint64_t start)
{
	return (get_time_in_ms() - start);
}

void	print_msg(t_philo	*philo, char	*msg)
{
	pthread_mutex_lock(&philo->general_data->mute);
	if (!philo->general_data->stop_sym)
		printf("%lu %zu %s\n", elapsed_time(philo->general_data->start_time),
			philo->num, msg);
	pthread_mutex_unlock(&philo->general_data->mute);
}

bool	wait_ms(uint64_t	ms)
{
	uint64_t	wait_start;

	wait_start = get_time_in_ms();
	while (elapsed_time(wait_start) < ms)
		usleep(100);
	return (1);
}

bool	stop_simulation(t_philo	*philo)
{
	pthread_mutex_lock(&philo->general_data->mute);
	if (philo->general_data->stop_sym)
		return (pthread_mutex_unlock(&philo->general_data->mute), 1);
	pthread_mutex_unlock(&philo->general_data->mute);
	return (0);
}
