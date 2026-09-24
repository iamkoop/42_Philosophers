/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:41:52 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/24 21:21:20 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*create_forks(int size)
{
	pthread_mutex_t	*fork_arr;
	int				i;

	fork_arr = malloc(sizeof(pthread_mutex_t) * size);
	if (!fork_arr)
		return (write(2, "Philo: fork_arr alloc failed\n", 30), NULL);
	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(&fork_arr[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork_arr[i]);
			free(fork_arr);
			return (write(2, "Philo: mutex_init fail\n", 24), NULL);
		}
	}
	return (fork_arr);
}

bool	general_data_init(t_data	*data)
{
	data->forks = create_forks(data->number_of_philosophers);
	if (!data->forks)
		return (0);
	if (pthread_mutex_init(&data->mute, NULL) != 0)
	{
		cleanup_forks(data->forks, data->number_of_philosophers);
		return (write(2, "Philo: mutex_init fail\n", 24), 0);
	}
	if (pthread_mutex_init(&data->start_sim, NULL) != 0)
	{
		cleanup_forks(data->forks, data->number_of_philosophers);
		return (write(2, "Philo: mutex_init fail\n", 24), 0);
	}
	return (1);
}

t_philo	*philos_init(pthread_mutex_t	*forks, t_data	*data, size_t size)
{
	t_philo			*philo_data;
	size_t			i;

	philo_data = malloc(sizeof(t_philo) * size);
	if (!philo_data)
		return (write(2, "Philo: philo_data alloc failed\n", 32), NULL);
	i = 0;
	while (i < size)
	{
		philo_data[i].num = i +1;
		philo_data[i].general_data = data;
		philo_data[i].times_eaten = 0;
		if (i == 0)
			philo_data[i].left_fork = &forks[size - 1];
		else
			philo_data[i].left_fork = &forks[i - 1];
		philo_data[i].right_fork = &forks[i];
		i++;
	}
	return (philo_data);
}
