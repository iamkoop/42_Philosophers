/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 15:32:56 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/21 11:35:18 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void cleanup_forks(pthread_mutex_t	*forks, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void cleanup_general_data(t_data *data)
{
	cleanup_forks(data->forks, data->input.number_of_philosophers);
	pthread_mutex_destroy(&data->sym);
	pthread_mutex_destroy(&data->print_protection);
	pthread_mutex_destroy(&data->philo_died);
}
