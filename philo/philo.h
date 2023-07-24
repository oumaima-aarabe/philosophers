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

/****************************************************************/
/************************STRUCTS*********************************/


typedef struct s_data
{
	int	philo_sum;
	int	t2_eat;
	int	t2_die;
	int	t2_sleep;
	int	alll_alive;
	int	all_ate;
	pthread_mutex_t	*forks;

}	t_data;

typedef struct s_philo
{
	int		id;
	int		l_fork;
	int		r_fork;
	int		last_meal;
	t_data	thread_dtls;

}	t_philo;

/****************************************************************/
/************************ROUTINE_FUNCTIONS************************/

/****************************************************************/
/************************INIT_FUNCTIONS**************************/

/****************************************************************/
/************************ERROR_MANAGE_FUNCS**********************/


/****************************************************************/
/************************UTILS_FUNTIONS**************************/

int		ft_strlen(char *s);
void	ft_putendl_fd(char *s, int fd);

/****************************************************************/

#endif