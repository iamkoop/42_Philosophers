/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_of_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:17:36 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/24 20:23:26 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitor(void	*ptr)
{
	t_philo	*philos;
	size_t	i;
	size_t size;
	size_t	cnt;

	philos = (t_philo	*)ptr;
	

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
			if(get_time_in_ms() - philos[i].t_since_last_meal >= philos->general_data->time_to_die)
			{
				printf("%lu %zu died\n", get_time_in_ms() - philos[i].general_data->start_time, philos[i].num);
				philos[i].general_data->stop_sym = 1;
				pthread_mutex_unlock(&philos[i].general_data->mute);
				return(NULL);
			}
			if(philos[i].general_data->min_eating_cnt > 0)
			{
				if(philos->general_data->min_eating_cnt <= philos[i].times_eaten)
					cnt++;
				if(cnt == size)
				{
					philos[i].general_data->stop_sym = 1;
					pthread_mutex_unlock(&philos[i].general_data->mute);
					return(NULL);
				}
			}
			pthread_mutex_unlock(&philos[i].general_data->mute);
			i++;
			usleep(50);
		}
	}
	return(NULL);
}

bool run_simulation(t_philo			*philos_data, t_data	*data)
{
	ssize_t		size;
	ssize_t		i;
	ssize_t		t;
	bool		ret;

	i = 0;
	ret = 1;
	size = philos_data[i].general_data->number_of_philosophers;
	pthread_mutex_lock(&data->start_sim);
	if(pthread_create(&data->monitor, NULL, monitor, philos_data))
	{
		perror("Philo: ");
		return (0);
	}
	while (i < size)
	{
		if (pthread_create(&philos_data[i].thread_id, NULL, philo, &philos_data[i]) != 0)
		{
			philos_data->general_data->stop_sym = 1;
			break;
		}
		i++;
	}
	t = 0;
	philos_data->general_data->start_time = get_time_in_ms();
	while (t < i)
	{
		philos_data[t].t_since_last_meal = philos_data->general_data->start_time;
		t++;
	}
	pthread_mutex_unlock(&data->start_sim);
	i--;
	while (i > -1)
	{
		pthread_join(philos_data[i].thread_id, NULL);
		i--;
	}
	pthread_join(data->monitor, NULL);
	return(ret);
}
