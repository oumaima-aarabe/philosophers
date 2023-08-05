#ifndef PHILO_H
# define PHILO_H

/************************INCLUDES********************************/

#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

/****************************************************************/
/************************STRUCTS*********************************/


typedef struct s_data
{
	int				philo_sum;
	int				t2_eat;
	int				t2_die;
	pthread_mutex_t	saba;
	pthread_mutex_t	printing;
	int				t2_sleep;
	int				nbr_meals;
	int				alll_alive;
	long long		start;
	int				all_ate;
	void			*state;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	long long		current_time;
	long long		deadline;
	int				meals_c;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

/****************************************************************/
/************************ROUTINE_FUNCTIONS************************/
void    *manage_print(t_philo *philo, int action);
long long gettime();
void	my_usleep(int t);
/****************************************************************/
/************************INIT_FUNCTIONS**************************/

/****************************************************************/
/************************ERROR_MANAGE_FUNCS**********************/


/****************************************************************/
/************************UTILS_FUNTIONS**************************/

int		ft_strlen(char *s);
void	ft_putendl_fd(char *s, int fd);
int	ft_atoi(const char *str);
int	test_limits(int ac, char **av);

/****************************************************************/

#endif