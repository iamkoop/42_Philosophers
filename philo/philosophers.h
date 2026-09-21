/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:16:17 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/21 12:27:13 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_parsed_input
{
	size_t		number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	min_eating_cnt;
}	t_parsed_input;

typedef struct s_data
{
	t_parsed_input	input;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sym;
	pthread_mutex_t	print_protection;
	pthread_mutex_t philo_died; //if a philo died we stop all others
	pthread_t		monitor;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	size_t			num;
	t_data			general_data;
	size_t			times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

//cleanup
void	cleanup_forks(pthread_mutex_t	*forks, int size);
void	cleanup_general_data(t_data *data);

//init
bool	parse_data(int argc, char	**argv, t_parsed_input	*data);
t_philo	*philos_init(pthread_mutex_t	*forks, t_data	data, size_t size);
bool	general_data_init(t_data	*data, t_parsed_input	input);

void	*philo(void *ptr);
bool	run_simulation(t_philo			*philos_data);
int		main(int argc, char	**argv);

#endif