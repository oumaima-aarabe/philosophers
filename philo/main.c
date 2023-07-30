#include "philo.h"



long long gettime()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	my_usleep(int t)
{
	long long	dl;
	dl = gettime() + t;
	while(gettime() < dl)
		usleep(100);
}
void	ham_ham(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	printf("%lld philo %d has taken a fork\n",gettime() - philo->data->start, philo->id);
	pthread_mutex_lock(philo->r_fork);
	printf("%lld philo %d has taken a fork\n",gettime() - philo->data->start, philo->id);
	pthread_mutex_lock(&philo->data->saba);
	philo->data->deadline = gettime() + philo->data->t2_die;
	philo->meals_c++;
	pthread_mutex_unlock(&philo->data->saba);
	printf("%lld philo %d is eating\n",gettime() - philo->data->start, philo->id);
	my_usleep(philo->data->t2_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("%lld philo %d is sleeping\n",gettime() - philo->data->start, philo->id);
	my_usleep(philo->data->t2_sleep);
	printf("%lld philo %d is thinking\n",gettime() - philo->data->start, philo->id);
}

int	death_check(t_philo *philo)
{
	int status;
	pthread_mutex_lock(&philo->data->saba);
	status = gettime() < philo->data->deadline;
	pthread_mutex_unlock(&philo->data->saba);
	return (status);
}
#include <limits.h>
int	routine(t_philo *philo)
{
	if (!(philo->id % 2))
		my_usleep(philo->data->t2_eat);
	philo->data->deadline = LLONG_MAX;
	philo->current_time = gettime();
	while (death_check(philo))
	{
		ham_ham(philo);
	}


}

int main(int ac, char **av)
{
	t_data data;
	if (ac < 5 || ac > 7)
		ft_putendl_fd("wrong number of args!", 2);
	if (test_limits(ac, av))
		return (1);
	data.philo_sum = ft_atoi(av[1]);
	data.t2_die = ft_atoi(av[2]);
	data.t2_eat = ft_atoi(av[3]);
	data.t2_sleep = ft_atoi(av[4]);
	data.nbr_meals = -1;
	data.alll_alive = 1;
	if (ac == 6)
		data.nbr_meals = ft_atoi(av[5]);
	int i = 0;
	pthread_mutex_init(&data.saba, NULL);
	t_philo	ph[200];
	while (i < data.philo_sum)
	{
		ph[i].meals_c = 0;
		ph[i].data = &data;
		ph[i].id = i + 1;
		pthread_mutex_init(&ph[i++].l_fork, NULL);
	}
	ph[0].r_fork = &ph[data.philo_sum - 1].l_fork;
	i = 0;
	while (i < data.philo_sum - 1)
	{
		ph[i + 1].r_fork = &ph[i].l_fork;
		i++;
	}
	i = 0;
	data.start = gettime();
	while (i < data.philo_sum)
		pthread_create(&ph[i].thread, NULL, (void *)routine, &ph[i++]);
	i = 0;
	while (i < data.philo_sum)
		pthread_join(ph[i++].thread, NULL);
}
