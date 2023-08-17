/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:30:53 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/16 08:48:42 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_check_var(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->data->saba))
		return (0);
	if (!ph->data->alll_alive || ph->data->all_ate)
		return (pthread_mutex_unlock(&ph->data->saba), 0);
	return (pthread_mutex_unlock(&ph->data->saba), 1);
}

void	update_data(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->data->saba))
		return ;
	if (!ph->eet)
	{
		ph->deadline = gettime() + ph->data->t2_die;
		ph->meals_c++;
		ph->eet = true;
	}
	else if (ph->eet)
		ph->eet = false;
	pthread_mutex_unlock(&ph->data->saba);
}

void	*ham_ham(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->l_fork))
		return (NULL);
	if (manage_print(philo, 1))
		return (pthread_mutex_unlock(&philo->l_fork), "done");
	if (philo->data->philo_sum == 1)
		return (pthread_mutex_unlock(&philo->l_fork), "done");
	if (pthread_mutex_lock(philo->r_fork))
		return (pthread_mutex_unlock(&philo->l_fork), NULL);
	if (manage_print(philo, 1))
		return (pthread_mutex_unlock(&philo->l_fork), \
		pthread_mutex_unlock(philo->r_fork), "done");
	update_data(philo);
	if (manage_print(philo, 2))
		return ("done");
	my_usleep(philo->data->t2_eat);
	update_data(philo);
	if (pthread_mutex_unlock(&philo->l_fork) || \
	pthread_mutex_unlock(philo->r_fork))
		return (NULL);
	if (manage_print(philo, 3))
		return ("done");
	my_usleep(philo->data->t2_sleep);
	if (manage_print(philo, 4))
		return ("done");
	return (NULL);
}

void	routine(t_philo *philo)
{
	if (!((philo->id) % 2))
		my_usleep(philo->data->t2_eat);
	while (2307)
	{
		if (!status_check_var(philo))
			break ;
		if (ham_ham(philo))
			return ;
	}
	return ;
}
