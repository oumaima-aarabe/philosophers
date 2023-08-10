/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 05:15:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/10 06:13:45 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *ph, long long start)
{
	int status = 1;
	if (pthread_mutex_lock(&ph->data->saba))
		return (0);
	if(!ph->data->alll_alive)
		return (pthread_mutex_unlock(&ph->data->saba), 0);
	usleep(1);
	if(!ph->eet && start > ph->deadline)
	{
		status = 0;
		ph->data->alll_alive = 0;
		printf("%lld philo %d has died\n",gettime() - ph->data->start, ph->id);
	}
	return (pthread_mutex_unlock(&ph->data->saba), status);
}

int	meal_counter_check(t_philo *ph, int *status)
{
	int sum = ph->data->philo_sum;
	int nbr_m = ph->data->nbr_meals;

	if(pthread_mutex_lock(&ph->data->saba))
		return(1);
	if (ph->data->all_ate)
		return (pthread_mutex_unlock(&ph->data->saba), 1);
	if (ph->meals_c == nbr_m && !ph->checked)
	{
			ph->checked = 1;
			(*status)++;
	}
	else if (ph->meals_c != nbr_m)
		return(pthread_mutex_unlock(&ph->data->saba), 0);
	if (*status == sum)
		ph->data->all_ate = 1;
	return(pthread_mutex_unlock(&ph->data->saba), *status == sum);
}

int	mcc_var(t_philo *ph)
{
	if(pthread_mutex_lock(&ph->data->saba))
		return(1);
	if(ph->data->all_ate)
		return (pthread_mutex_unlock(&ph->data->saba), 1);
	return (pthread_mutex_unlock(&ph->data->saba), 0);
}

int	death_check_var(t_philo *ph)
{
	if(pthread_mutex_lock(&ph->data->saba))
		return(0);
	if(!ph->data->alll_alive)
		return (pthread_mutex_unlock(&ph->data->saba), 0);
	return (pthread_mutex_unlock(&ph->data->saba), 1);
}


void	update_data(t_philo *ph)
{
	if(pthread_mutex_lock(&ph->data->saba))
        return;
	if (!ph->eet)
	{
		ph->deadline = gettime() + ph->data->t2_die;
		ph->meals_c++;
		ph->eet = true;	
	}
	else if(ph->eet)
		ph->eet = false;
    pthread_mutex_unlock(&ph->data->saba);
}
void	*ham_ham(t_philo *philo)
{
	if(pthread_mutex_lock(&philo->l_fork))
		return(NULL);
	if (manage_print(philo, 1))
		return ("done");
	if(philo->data->philo_sum == 1)
		return (pthread_mutex_unlock(&philo->l_fork), "done");
	if(pthread_mutex_lock(philo->r_fork))
		return(NULL);
	if (manage_print(philo, 1))
		return ("done");
	update_data(philo);
	if (manage_print(philo, 2))
		return ("done");
	my_usleep(philo->data->t2_eat);
	update_data(philo);
	if(pthread_mutex_unlock(&philo->l_fork) ||\
	pthread_mutex_unlock(philo->r_fork))
        return (NULL);
	if (manage_print(philo, 3))
		return ("done");
	my_usleep(philo->data->t2_sleep);
	if (manage_print(philo, 4))
		return ("done");
	return (NULL);
}

void	overseer(t_philo *ph)
{
	int i = 0;
	int sum = ph[0].data->philo_sum;
	int status = 0;
	while ("ghayboba")
	{
		 i = 0;
		long long start = gettime();
		while (i < sum)
		{
			if(!death_check(&ph[i], start))
				return;
			if (meal_counter_check(&ph[i], &status))
				return ;
			i++;
		}
		usleep(100);
	}
}

void	routine(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->saba))
		return ;
	philo->deadline = gettime() + philo->data->t2_die;
	pthread_mutex_unlock(&philo->data->saba);
	if (!((philo->id ) % 2))
		my_usleep(philo->data->t2_eat);
	while ("ghayboba")
	{
		if(!death_check_var(philo) || mcc_var(philo))
			break ;
		if(ham_ham(philo))
			return ;
	}
	return ;
}

int main(int ac, char **av)
{
	t_data data;
	int i;
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
