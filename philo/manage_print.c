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

void    *manage_print(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->saba);
    if(!philo->data->alll_alive)
	{
		pthread_mutex_unlock(&philo->data->saba);
		return ("dead");
	}
    if(action == 1)
	    printf("%lld philo %d has taken a fork\n",gettime() - philo->data->start, philo->id);
    else if (action == 2)
	    printf("%lld philo %d is eating\n",gettime() - philo->data->start, philo->id);
    else if (action == 3)
	    printf("%lld philo %d is sleeping\n",gettime() - philo->data->start, philo->id);
    else if (action == 4)
	    printf("%lld philo %d is thinking\n",gettime() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->saba);
    return(NULL);
    
}