/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:46:58 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/20 18:13:32 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo	*)ptr;
	printf("Philo num: %zu\n", philo->num);
	printf("Philo eat: %d\n", philo->number_of_times_each_philosopher_must_eat);
	return (NULL);
}