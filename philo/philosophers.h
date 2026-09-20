/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:16:17 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/20 17:46:36 by nildruon         ###   ########.fr       */
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

typedef struct s_parsed_input
{
	size_t		number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	number_of_times_each_philosopher_must_eat;
}	t_parsed_input;

typedef struct s_philo
{
	size_t			num;
	pthread_t		id;
	int				times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				number_of_times_each_philosopher_must_eat;
}	t_philo;

typedef struct s_data
{
	t_parsed_input	general_data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sym;
	pthread_mutex_t	print_protection;
	pthread_mutex_t philo_died; //if a philo died we stop all others
	pthread_t		monitor;
	t_philo			*philo_data;
}	t_data;

void	cleanup_forks(pthread_mutex_t	*forks, int size);
void	*philo(void *ptr);
void	create_threads(t_data data, size_t size);
bool	data_init(t_data	*data, t_parsed_input	input);
int		parse_data(int argc, char	**argv, t_parsed_input	*data);
int		main(int argc, char	**argv);

#endif