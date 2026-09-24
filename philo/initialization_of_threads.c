/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_of_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:17:36 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/24 22:34:35 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	monitor_help(t_philo	*philo, size_t	size, size_t	*cnt)
{
	if (get_time_in_ms() - philo->t_since_last_meal
		>= philo->general_data->time_to_die)
	{
		printf("%lu %zu died\n", get_time_in_ms()
			- philo->general_data->start_time, philo->num);
		philo->general_data->stop_sym = 1;
		pthread_mutex_unlock(&philo->general_data->mute);
		return (0);
	}
	if (philo->general_data->min_eating_cnt > 0)
	{
		if (philo->general_data->min_eating_cnt <= philo->times_eaten)
			(*cnt)++;
		if (*cnt == size)
		{
			philo->general_data->stop_sym = 1;
			pthread_mutex_unlock(&philo->general_data->mute);
			return (0);
		}
	}
	return (1);
}

static void	*monitor(void	*ptr)
{
	t_philo	*philos;
	size_t	i;
	size_t	size;
	size_t	cnt;

	philos = (t_philo *)ptr;
	i = 0;
	cnt = 0;
	size = philos[i].general_data->number_of_philosophers;
	pthread_mutex_lock(&philos[i].general_data->start_sim);
	pthread_mutex_unlock(&philos[i].general_data->start_sim);
	while (1)
	{
		i = 0;
		cnt = 0;
		while (i < size)
		{
			pthread_mutex_lock(&philos[i].general_data->mute);
			if (!monitor_help(&philos[i], size, &cnt))
				return (NULL);
			pthread_mutex_unlock(&philos[i++].general_data->mute);
			usleep(50);
		}
	}
	return (NULL);
}

static bool	run_sim_help(t_philo	*philos_data, t_data	*data,
	ssize_t	*i, ssize_t	size)
{
	ssize_t		j;

	j = 0;
	if (pthread_create(&data->monitor, NULL, monitor, philos_data))
		return (0);
	while (*i < size)
	{
		if (pthread_create(&philos_data[*i].thread_id,
				NULL, philo, &philos_data[*i]) != 0)
		{
			philos_data->general_data->stop_sym = 1;
			break ;
		}
		(*i)++;
	}
	j = 0;
	philos_data->general_data->start_time = get_time_in_ms();
	while (j < *i)
	{
		philos_data[j].t_since_last_meal
			= philos_data->general_data->start_time;
		j++;
	}
	return (1);
}

bool	run_simulation(t_philo	*philos_data, t_data	*data)
{
	ssize_t		size;
	ssize_t		i;
	bool		ret;

	i = 0;
	ret = 1;
	size = philos_data[i].general_data->number_of_philosophers;
	pthread_mutex_lock(&data->start_sim);
	if (!run_sim_help(philos_data, data, &i, size))
		return (pthread_mutex_unlock(&data->start_sim), 0);
	pthread_mutex_unlock(&data->start_sim);
	i--;
	while (i > -1)
	{
		pthread_join(philos_data[i].thread_id, NULL);
		i--;
	}
	pthread_join(data->monitor, NULL);
	return (ret);
}
