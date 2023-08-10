/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:30:53 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/10 06:48:59 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mcc_var(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->data->saba))
		return (1);
	if (ph->data->all_ate)
		return (pthread_mutex_unlock(&ph->data->saba), 1);
	return (pthread_mutex_unlock(&ph->data->saba), 0);
}

int	death_check_var(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->data->saba))
		return (0);
	if (!ph->data->alll_alive)
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
		return ("done");
	if (philo->data->philo_sum == 1)
		return (pthread_mutex_unlock(&philo->l_fork), "done");
	if (pthread_mutex_lock(philo->r_fork))
		return (NULL);
	if (manage_print(philo, 1))
		return ("done");
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
	if (pthread_mutex_lock(&philo->data->saba))
		return ;
	philo->deadline = gettime() + philo->data->t2_die;
	pthread_mutex_unlock(&philo->data->saba);
	if (!((philo->id) % 2))
		my_usleep(philo->data->t2_eat);
	while ("ghayboba")
	{
		if (!death_check_var(philo) || mcc_var(philo))
			break ;
		if (ham_ham(philo))
			return ;
	}
	return ;
}
