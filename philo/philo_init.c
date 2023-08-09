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
		if (data->nbr_meals == -1)
			return (1);
	}
	return (0);
}

int	init_philo(t_data data, t_philo *ph)
{
	int i = 0;
	while (i < data.philo_sum)
	{
		ph[i].meals_c = 0;
		ph[i].checked = 0;
		ph[i].data = &data;
		ph[i].id = i + 1;
		if (pthread_mutex_init(&ph[i++].l_fork, NULL))
			return(1);
	}
	ph[0].r_fork = &ph[data.philo_sum - 1].l_fork;
	i = 0;
	while (i < data.philo_sum - 1)
	{
		ph[i + 1].r_fork = &ph[i].l_fork;
		i++;
	}
	return (0);
}
