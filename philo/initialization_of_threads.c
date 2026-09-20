/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_of_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:17:36 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/20 17:57:45 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void create_threads(t_data data, size_t size)
{
	pthread_t thread_id_arr[size];
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&thread_id_arr[i], NULL, philo, &data.philo_data[i]) != 0)
		{
			perror("Philo: ");
			break;
		}
		i++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(thread_id_arr[i], NULL);
		i--;
	}
}
