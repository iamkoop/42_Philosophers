/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:15:34 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/23 13:42:00 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char	**argv)
{
	t_data			data;
	t_philo			*philos_data;

	data = (t_data){0};
	if (!parse_data(argc, argv, &data))
		return (1);
	if (!general_data_init(&data))
		return (1);
	philos_data = philos_init(data.forks, &data, data.number_of_philosophers);
	if (!philos_data)
		return (cleanup_general_data(&data), 1);
	if (!run_simulation(philos_data, &data))
		return (cleanup_general_data(&data), 1);
	return (0);
}
