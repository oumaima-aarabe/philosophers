#include "philo.h"

int main(int ac, char **av)
{
	if (ac < 5 || ac > 7)
		ft_putendl_fd("wrong number of args!", 2);
	if (test_limits(ac, av))
}