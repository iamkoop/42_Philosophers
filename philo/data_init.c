/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:41:52 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/20 17:23:20 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*create_forks(int size)
{
	pthread_mutex_t	*fork_arr;
	int				i;

	fork_arr = malloc(sizeof(pthread_mutex_t) * size);
	if(!fork_arr)
		return (write(2, "Philo: fork_arr alloc failed\n", 30), NULL);
	i = -1;
	while (++i < size)
	{
		if(pthread_mutex_init(&fork_arr[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork_arr[i]);
			free(fork_arr);
			return (write(2, "Philo: mutex_init fail\n", 24), NULL);
		}
	}
	return (fork_arr);
}

static t_philo	*philos_data_init(t_parsed_input	input,
		pthread_mutex_t	*forks)
{
	t_philo			*philo_data;
	size_t			i;

	philo_data = malloc(sizeof(t_philo) * input.number_of_philosophers);
	if(!philo_data)
		return (write(2, "Philo: philo_data alloc failed\n", 32), NULL);
	i = 0;
	while (i < input.number_of_philosophers)
	{
		philo_data[i].num = i;
		philo_data[i].times_eaten = 0;
		if(i == 0)
			philo_data[i].left_fork = &forks[input.number_of_philosophers -1];
		else
			philo_data[i].left_fork = &forks[i];
		if(i == input.number_of_philosophers -1)
			philo_data[i].right_fork = &forks[0];
		else
			philo_data[i].right_fork = &forks[i];
		philo_data[i].number_of_times_each_philosopher_must_eat
			= input.number_of_times_each_philosopher_must_eat;
		i++;
	}
	return(philo_data);
}

bool data_init(t_data	*data, t_parsed_input	input)
{ 
	data->general_data = input;
	data->forks = create_forks(input.number_of_philosophers);
	if(!data->forks)
		return(0);
	data->philo_data = philos_data_init(input, data->forks);
	if(pthread_mutex_init(&data->sym, NULL) != 0)
	{
		cleanup_forks(data->forks, input.number_of_philosophers);
		return (write(2, "Philo: mutex_init fail\n", 24), 0);
	}
	if(pthread_mutex_init(&data->print_protection, NULL) != 0)
	{
		cleanup_forks(data->forks, input.number_of_philosophers);
		pthread_mutex_destroy(&data->sym);
		return (write(2, "Philo: mutex_init fail\n", 24), 0);
	}
	if(pthread_mutex_init(&data->philo_died, NULL) != 0)
	{
		cleanup_forks(data->forks, input.number_of_philosophers);
		pthread_mutex_destroy(&data->sym);
		pthread_mutex_destroy(&data->print_protection);
		return (write(2, "Philo: mutex_init fail\n", 24), 0);
	}
	return(1);
}

