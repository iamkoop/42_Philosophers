/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 16:15:34 by nildruon          #+#    #+#             */
/*   Updated: 2026/09/16 18:41:15 by nildruon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char	**argv)
{
	t_philo_data	data;

	data = (t_philo_data){0};
	if (!parse_data(argc, argv, &data))
		return (1);
	return (0);
}
