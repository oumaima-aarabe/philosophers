/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 05:15:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/16 08:06:39 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	t_philo	ph[200];

	if (init_data(ac, av, &data))
		return (manage_errors(1), 1);
	if (pthread_mutex_init(&data.saba, NULL))
		return (manage_errors(3), 1);
	if (init_philo(&data, ph, &i))
	{
		while (i--)
			pthread_mutex_destroy(&ph[i].l_fork);
		return (pthread_mutex_destroy(&data.saba), manage_errors(2), 1);
	}
	overseer(ph);
	i = -1;
	while (++i < data.philo_sum)
		pthread_join(ph[i].thread, NULL);
	i = -1;
	pthread_mutex_destroy(&data.saba);
	while (++i < data.philo_sum)
		pthread_mutex_destroy(&ph[i].l_fork);
}
