/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:12:01 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/23 12:01:55 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *c)
{
	unsigned long		res;
	int					i;

	i = 0;
	res = 0;
	while (c[i] == ' ' || c[i] == '\t' || c[i] == '\n' || c[i] == '\v'
		|| c[i] == '\f' || c[i] == '\r')
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			return (-1);
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		res = (res * 10) + (c[i] - '0');
		i++;
	}
	if (res > INT_MAX)
		return (-1);
	return ((int)res);
}

void	ft_exit(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int	is_notdigit(char *av)
{
	int	i;

	i = -1;
	while (av[++i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
	}
	return (0);
}

bool	someone_dead(t_prog *prog)
{
	bool	res;

	pthread_mutex_lock(&prog->dead_lock);
	res = prog->someone_dead;
	pthread_mutex_unlock(&prog->dead_lock);
	if (res)
		return (true);
	else
		return (false);
}

void	precise_sleep(t_prog *prog, long ms)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < ms)
	{
		if (someone_dead(prog))
			break ;
		usleep(100);
	}
}
