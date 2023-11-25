/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:24:50 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 16:06:55 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_only_one_philo(t_data *data)
{
	printf("%s [%ld] philo [0]]: take a fork  {-------0}%s\n", COLOR_BLUE,
		(get_time() - data->start_time), COLOR_RESET);
	usleep(data->time_to_die * 1000);
	printf("%s [%ld] philo [0]]: is dead  {-------0}%s\n", COLOR_RED,
		(get_time() - data->start_time), COLOR_RESET);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philos;

	data = NULL;
	philos = NULL;
	if (!is_valid_args(ac, av))
		return (EXIT_FAILURE);
	data = init_data(data, ac, av);
	if (data->nb_philos == 1)
	{
		handle_only_one_philo(data);
		free(data);
		return (EXIT_SUCCESS);
	}
	philos = init_philos(data);
	init_mutex(philos, data);
	set_philos_forks_id(philos, data);
	create_threads_philos(philos, data);
	destroy_mutex(philos, data);
	return (EXIT_SUCCESS);
}
