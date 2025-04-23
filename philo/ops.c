/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:43:27 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/23 14:19:35 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
}

void	eat(t_philo *philo)
{
	lock_forks(philo);
	write_stat(gettime() - philo->prog->s_time, philo->id, 'f',
		philo->prog);
	write_stat(gettime() - philo->prog->s_time, philo->id, 'f',
		philo->prog);
	pthread_mutex_lock(&philo->meal_lock);
	philo->lastmeal_time = gettime();
	philo->meal_count++;
	if (philo->prog->meal_num > 0 && !philo->finished
		&& philo->meal_count >= philo->prog->meal_num)
	{
		philo->prog->finished_count++;
		philo->finished = 1;
	}
	pthread_mutex_unlock(&philo->meal_lock);
	write_stat(gettime() - philo->prog->s_time, philo->id, 'e',
		philo->prog);
	precise_sleep(philo->prog, philo->prog->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philosleep(t_philo *philo)
{
	write_stat(gettime() - philo->prog->s_time, philo->id, 's',
		philo->prog);
	precise_sleep(philo->prog, philo->prog->time_to_sleep);
}

void	think(t_philo *philo)
{
	long	think;

	think = philo->prog->time_to_die
		- (philo->prog->time_to_eat + philo->prog->time_to_sleep);
	write_stat(gettime() - philo->prog->s_time, philo->id, 't',
		philo->prog);
	if (think > 1)
		precise_sleep(philo->prog, think);
}

void	onephilo(t_philo *philo)
{
	write_stat(gettime() - philo->prog->s_time, philo->id, 'f',
		philo->prog);
	precise_sleep(philo->prog, philo->prog->time_to_die);
	write_stat(gettime() - philo->prog->s_time, philo->id, 'd',
		philo->prog);
	free_exit(philo->prog, 0);
}
