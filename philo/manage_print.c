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
	if(pthread_mutex_lock(&philo->data->saba))
		return(NULL);
    if(!philo->data->alll_alive || philo->data->all_ate)
		return (pthread_mutex_unlock(&philo->data->saba), "done");
    if(action == 1)
	    printf("%lld philo %d has taken a fork\n",gettime() \
		- philo->data->start, philo->id);
    else if (action == 2)
	    printf("%lld philo %d is eating\n",gettime() \
		- philo->data->start, philo->id);
    else if (action == 3)
	    printf("%lld philo %d is sleeping\n",gettime() \
		- philo->data->start, philo->id);
	else if (action == 4)
	    printf("%lld philo %d is thinking\n",gettime() \
		- philo->data->start, philo->id);
    return(pthread_mutex_unlock(&philo->data->saba), NULL);
    
}

void manage_errors(int c)
{
	if(c == 1)
		ft_putendl_fd("invalid args", 2);
	if(c == 2)
		ft_putendl_fd("thread creation failed", 2);
	if(c == 3)
		ft_putendl_fd("mutex failed", 2);
}