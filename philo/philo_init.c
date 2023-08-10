/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:22:17 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/10 06:45:36 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 7)
		return (1);
	data->philo_sum = ft_atoi(av[1]);
	data->t2_die = ft_atoi(av[2]);
	data->t2_eat = ft_atoi(av[3]);
	data->t2_sleep = ft_atoi(av[4]);
	if (!data->philo_sum || !data->t2_die || !data->t2_eat ||!data->t2_sleep)
		return (1);
	data->nbr_meals = -1;
	data->alll_alive = 1;
	data->all_ate = 0;
	if (ac == 6)
	{
		data->nbr_meals = ft_atoi(av[5]);
		if (data->nbr_meals == 0)
			return (1);
	}
	return (0);
}

void	init_forks(t_philo *ph, t_data data)
{
	int	i;

	ph[0].r_fork = &ph[data.philo_sum - 1].l_fork;
	i = 0;
	while (i < data.philo_sum - 1)
	{
		ph[i + 1].r_fork = &ph[i].l_fork;
		i++;
	}
}

int	init_philo(t_data *data, t_philo *ph, int *i)
{
	*i = 0;
	while (*i < data->philo_sum)
		if (pthread_mutex_init(&ph[(*i)++].l_fork, NULL))
			return (1);
	init_forks(ph, *data);
	data->start = gettime();
	*i = -1;
	while (++(*i) < data->philo_sum)
	{
		ph[*i].meals_c = 0;
		ph[*i].checked = 0;
		ph[*i].data = data;
		ph[*i].id = *i + 1;
		ph[*i].eet = false;
		if (pthread_create(&ph[*i].thread, NULL, (void *)routine, &ph[*i]))
			return (*i = data->philo_sum, 1);
		usleep(100);
	}
	return (0);
}
