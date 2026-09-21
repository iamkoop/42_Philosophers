/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:46:58 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/21 12:47:04 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo(void *ptr)
{
	struct timeval time;
	t_philo	*philo;

	philo = (t_philo	*)ptr;
	if(gettimeofday(&time, NULL) == -1)
		return(NULL);
	printf("Philo num: %zu\n", philo->num);
	printf("Philo thread_id: %zu\n", philo->thread_id);
	printf("Philo time: %ld\n", time.tv_usec);
	return (NULL);
}