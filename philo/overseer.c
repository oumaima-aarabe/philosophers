/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:32:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/16 04:43:16 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *ph, long long start)
{
	int	status;

	status = 1;
	if (pthread_mutex_lock(&ph->data->saba))
		return (0);
	if (!ph->data->alll_alive)
		return (pthread_mutex_unlock(&ph->data->saba), 0);
	usleep(1);
	if (!ph->eet && start > ph->deadline)
	{
		status = 0;
		ph->data->alll_alive = 0;
		printf("%lld philo %d has died\n", gettime() - ph->data->start, ph->id);
	}
	return (pthread_mutex_unlock(&ph->data->saba), status);
}

int	meal_counter_check(t_philo *ph, int *status)
{
	int	sum;
	int	nbr_m;

	sum = ph->data->philo_sum;
	nbr_m = ph->data->nbr_meals;
	if (pthread_mutex_lock(&ph->data->saba))
		return (1);
	if (ph->data->all_ate)
		return (pthread_mutex_unlock(&ph->data->saba), 1);
	if (ph->meals_c == nbr_m && !ph->checked)
	{
		ph->checked = 1;
		(*status)++;
	}
	else if (ph->meals_c != nbr_m)
		return (pthread_mutex_unlock(&ph->data->saba), 0);
	if (*status == sum)
		ph->data->all_ate = 1;
	return (pthread_mutex_unlock(&ph->data->saba), *status == sum);
}

void	overseer(t_philo *ph)
{
	int			i;
	int			sum;
	int			status;
	long long	start;

	i = 0;
	status = 0;
	sum = ph[0].data->philo_sum;
	while (2307)
	{
		i = 0;
		start = gettime();
		while (i < sum)
		{
			if (!death_check(&ph[i], start))
				return ;
			if (meal_counter_check(&ph[i], &status))
				return ;
			i++;
		}
		usleep(100);
	}
}
