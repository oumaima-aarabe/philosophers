/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:50:24 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/10 06:50:45 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/************************INCLUDES********************************/

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

/****************************************************************/
/************************STRUCTS*********************************/

typedef struct s_data
{
	int				philo_sum;
	int				t2_eat;
	int				t2_die;
	pthread_mutex_t	saba;
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
	bool			eet;
	int				meals_c;
	pthread_t		thread;
	t_data			*data;
	int				checked;
}	t_philo;

/****************************************************************/
/************************ROUTINE_FUNCTIONS************************/

void		*manage_print(t_philo *philo, int action);
void		routine(t_philo *philo);

/****************************************************************/
/************************OVERSEERER******************************/

void		overseer(t_philo *ph);

/****************************************************************/
/************************INIT_FUNCTIONS**************************/

int			init_data(int ac, char **av, t_data *data);
int			init_philo(t_data *data, t_philo *ph, int *i);

/****************************************************************/
/************************ERROR_MANAGE_FUNCS**********************/

void		manage_errors(int c);

/****************************************************************/
/************************UTILS_FUNTIONS**************************/

int			ft_strlen(char *s);
void		ft_putendl_fd(char *s, int fd);
long long	gettime(void);
void		my_usleep(int t);
int			ft_atoi(char *str);

/****************************************************************/

#endif