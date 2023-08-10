/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:20:50 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/08/10 06:27:10 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	char	*c;
	
	if(!s)
		return (0);
	c = s;
	while (*c)
		c++;
	return ((int)(c - s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}


int	ft_atoi(char *str)
{
	long	nbr;
	int		sign;
	int		i;

	sign = 1;
	nbr = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] > 7 && str[i] < 14))
			i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	if(str[i])
		return(0);
	return (sign * nbr);
}
