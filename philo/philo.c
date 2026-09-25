/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 22:46:58 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/25 12:57:17 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	thinking(t_philo	*philo)
{
	uint64_t	thinking;
	uint64_t	time_left;

	time_left = philo->general_data->time_to_die
		- (get_time_in_ms() - philo->t_since_last_meal);
	thinking = time_left / 2 + 1;
	if (stop_simulation(philo))
		return (0);
	print_msg(philo, "is thinking");
	if (stop_simulation(philo))
		return (0);
	if (!wait_ms(philo, thinking))
		return (0);
	return (1);
}

static bool	sleeping(t_philo	*philo)
{
	if (philo->general_data->number_of_philosophers > 1)
		print_msg(philo, "is sleeping");
	if (!wait_ms(philo, philo->general_data->time_to_sleep))
		return (0);
	return (1);
}

static void	unlock_forks(pthread_mutex_t *left, pthread_mutex_t *right)
{
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
}

static bool	eating(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork");
	if (philo->general_data->number_of_philosophers == 1)
	{
		wait_ms(philo, philo->general_data->time_to_die);
		return (pthread_mutex_unlock(philo->left_fork), 1);
	}
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->general_data->mute);
	philo->t_since_last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->general_data->mute);
	if (stop_simulation(philo))
		return (unlock_forks(philo->left_fork, philo->right_fork), 0);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "eating");
	if (!wait_ms(philo, philo->general_data->time_to_eat))
		return (unlock_forks(philo->left_fork, philo->right_fork), 0);
	pthread_mutex_lock(&philo->general_data->mute);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->general_data->mute);
	unlock_forks(philo->left_fork, philo->right_fork);
	return (1);
}

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->general_data->start_sim);
	pthread_mutex_unlock(&philo->general_data->start_sim);
	if (philo->num % 2 == 0)
		usleep(500);
	while (!stop_simulation(philo))
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}
