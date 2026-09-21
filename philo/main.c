/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:15:34 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/21 12:13:04 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char	**argv)
{
	t_parsed_input	input;
	t_data			data;
	t_philo			*philos_data;

	input = (t_parsed_input){0};
	if (!parse_data(argc, argv, &input))
		return (1);
	if(!general_data_init(&data, input))
		return (1);
	philos_data = philos_init(data.forks, data, input.number_of_philosophers);
	if(!philos_data)
		return(cleanup_general_data(&data), 1);
	if(!run_simulation(philos_data))
		return(cleanup_general_data(&data), 1);
	return (0);
}
