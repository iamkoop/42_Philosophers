/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_of_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:17:36 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/21 12:13:38 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



bool run_simulation(t_philo			*philos_data)
{
	size_t		size;
	size_t		i;
	bool		ret;

	i = 0;
	ret = 1;
	size = philos_data[i].general_data.input.number_of_philosophers;
	while (i < size)
	{
		if (pthread_create(&philos_data[i].thread_id, NULL, philo, &philos_data[i]) != 0)
		{
			perror("Philo: ");
			ret = 0;
			break ;
		}
		i++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(philos_data[i].thread_id, NULL);
		i--;
	}
	return(ret);
}
