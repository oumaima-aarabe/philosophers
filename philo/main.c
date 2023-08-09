#include "philo.h"

int	death_check(t_philo *ph, long long start)
{
	int status = 1;
	pthread_mutex_lock(&ph->data->saba);
	if(!ph->data->alll_alive)
	{
		pthread_mutex_unlock(&ph->data->saba);
		return (0);
	}
	usleep(1);
	if(start > ph->deadline)
	{
		status = 0;
		ph->data->alll_alive = 0;
		printf("%lld philo %d has died\n",gettime() - ph->data->start, ph->id);

	} 
	pthread_mutex_unlock(&ph->data->saba);
	return (status);
}

int	meal_counter_check(t_philo *ph, int *status)
{
	int i = -1;
	int sum = ph->data->philo_sum;
	int nbr_m = ph->data->nbr_meals;

	pthread_mutex_lock(&ph->data->saba);
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
	{
		ph->data->all_ate = 1;
	}
		// printf("status %d: %d \n", ph->id, *status);
	pthread_mutex_unlock(&ph->data->saba);
	return(*status == sum);
}

int	mcc_var(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->saba);
		// puts("here");
	if(ph->data->all_ate)
	{
		pthread_mutex_unlock(&ph->data->saba);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->saba);
	return (0);
}

int	death_check_var(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->saba);
	if(!ph->data->alll_alive)
	{
		pthread_mutex_unlock(&ph->data->saba);
		return (0);
	}
	pthread_mutex_unlock(&ph->data->saba);
	return (1);
}

void	*ham_ham(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	if (manage_print(philo, 1))
		return ("done");
	pthread_mutex_lock(philo->r_fork);
	if (manage_print(philo, 1))
		return ("done");
	pthread_mutex_lock(&philo->data->saba);
	philo->deadline = gettime() + philo->data->t2_die;
	philo->meals_c++;
	pthread_mutex_unlock(&philo->data->saba);
	if (manage_print(philo, 2))
		return ("done");
	my_usleep(philo->data->t2_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	pthread_mutex_lock(&philo->data->saba);
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
	{
		ft_putendl_fd("invalid args", 2);
		return (1);
	}
	pthread_mutex_init(&data.saba, NULL);
	if (init_philo(data, ph))
	{
		ft_putendl_fd("mutex failed", 2);
		return (1);
	}
	data.start  = gettime();
	i = -1;
	while (++i < data.philo_sum)
	{
		pthread_create(&ph[i].thread, NULL, (void *)routine, &ph[i]);
		usleep(100);
	}
	overseer(ph);
	printf("frh\n");
	i = -1;
	while (++i < data.philo_sum)
		pthread_join(ph[i].thread, NULL);
}
