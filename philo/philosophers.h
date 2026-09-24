/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:16:17 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/24 15:38:13 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_data
{
	size_t			number_of_philosophers;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		min_eating_cnt;
	size_t			eating_all_done;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mute;
	pthread_mutex_t	start_sim;
	bool			start;
	bool			stop_sym;
	pthread_t		monitor;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	size_t			num;
	t_data			*general_data;
	uint64_t		start;
	uint64_t		t_since_last_meal;
	size_t			times_eaten;
	bool			is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

//cleanup
void	cleanup_forks(pthread_mutex_t	*forks, int size);
void	cleanup_general_data(t_data *data);

//init
bool	parse_data(int argc, char	**argv, t_data	*data);
t_philo	*philos_init(pthread_mutex_t	*forks, t_data	*data, size_t size);
bool	general_data_init(t_data	*data);

void	*philo(void *ptr);
bool	run_simulation(t_philo	*philos_data, t_data	*data);
int		main(int argc, char	**argv);

#endif