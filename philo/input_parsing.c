/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:15:05 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/20 00:10:07 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size])
		size++;
	return (size);
}

static int	ft_compact_atoi(const char *nptr)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num);
}

static int	check_int_max(char	*curr_arg, int curr_arg_len)
{
	char	*err_msg;
	char	*int_max;
	bool	num_is_safe;
	size_t	i;

	i = 0;
	num_is_safe = 0;
	err_msg = "Philo: Input contains a num thats over int_max\n";
	int_max = "2147483647";
	while (curr_arg_len > 9 && curr_arg[i])
	{
		if (i > 9)
			return (write(2, err_msg, 48), -1);
		if (curr_arg[i] < int_max[i])
			num_is_safe = 1;
		if (!num_is_safe && curr_arg[i] > int_max[i])
			return (write(2, err_msg, 48), -1);
		i++;
	}
	return (ft_compact_atoi(curr_arg));
}

static int	num_parsing(char	*curr_arg)
{
	size_t	curr_arg_len;
	size_t	i;
	ssize_t	ret;

	i = 0;
	curr_arg_len = ft_strlen(curr_arg);
	if (curr_arg_len == 0)
		return (write(2, "Philo: args cannot be empty\n", 29), 0);
	while (curr_arg[i])
	{
		if (curr_arg[i] < '0' || curr_arg[i] > '9')
		{
			write(2, "Philo: args can only contain: digits 0-9\n", 42);
			return (0);
		}
		i++;
	}
	ret = check_int_max(curr_arg, curr_arg_len);
	if (ret == 0)
		write(2, "Philo: args have to be bigger than 0\n", 38);
	if (ret == -1)
		return (0);
	return (ret);
}

int	parse_data(int argc, char	**argv, t_parsed_input	*data)
{
	size_t	i;
	int	curr_param;

	if (argc < 5)
		return (write(2, "Philo: Not enough arguments passed\n", 35), 0);
	if (argc > 6)
		return (write(2, "Philo: Too many arguments passed\n", 33), 0);
	i = 0;
	while (argv[++i])
	{
		curr_param = num_parsing(argv[i]);
		if (!curr_param)
			return (0);
		if (i == 1)
			data->number_of_philosophers = curr_param;
		else if (i == 2)
			data->time_to_die = curr_param;
		else if (i == 3)
			data->time_to_eat = curr_param;
		else if (i == 4)
			data->time_to_sleep = curr_param;
		else if (i == 5)
			data->number_of_times_each_philosopher_must_eat = curr_param;
	}
	return (1);
}
