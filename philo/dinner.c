/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:37:04 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/23 14:21:08 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data)
{
	t_prog	*p;
	int		i;

	p = (t_prog *)data;
	while (!someone_dead(p))
	{
		i = -1;
		while (++i < p->nop)
		{
			pthread_mutex_lock(&p->philos[i].meal_lock);
			if (gettime() - p->philos[i].lastmeal_time > p->time_to_die)
			{
				pthread_mutex_unlock(&p->philos[i].meal_lock);
				write_stat((gettime() - p->s_time), p->philos[i].id, 'd', p);
				pthread_mutex_lock(&p->dead_lock);
				p->someone_dead = true;
				pthread_mutex_unlock(&p->dead_lock);
				break ;
			}
			pthread_mutex_unlock(&p->philos[i].meal_lock);
			if (p->finished_count >= p->nop)
				free_exit(p, 0);
		}
	}
	return (NULL);
}

void	write_stat(long time, int philo_id, char op, t_prog *prog)
{
	char	*msg;

	msg = NULL;
	if (op == 'f')
		msg = "has taken a fork";
	else if (op == 'e')
		msg = "is eating";
	else if (op == 's')
		msg = "is sleeping";
	else if (op == 't')
		msg = "is thinking";
	else if (op == 'd')
		msg = "died";
	if (someone_dead(prog) && op != 'd')
		return ;
	pthread_mutex_lock(&prog->write_lock);
	printf("%ld %d %s\n", time, philo_id, msg);
	pthread_mutex_unlock(&prog->write_lock);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(50);
	while (1)
	{
		if (someone_dead(philo->prog))
			break ;
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->prog->meal_num > 0 && philo->finished)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_lock);
		eat(philo);
		philosleep(philo);
		think(philo);
	}
	return (NULL);
}

void	dinner_start(t_prog *prog)
{
	int			i;

	prog->s_time = gettime();
	if (prog->nop == 1)
		onephilo(&prog->philos[0]);
	i = -1;
	while (++i < prog->nop)
		prog->philos[i].lastmeal_time = prog->s_time;
	i = -1;
	while (++i < prog->nop)
	{
		if (pthread_create(&prog->philos[i].t_id, NULL,
				routine, &prog->philos[i]) != 0)
			break ;
	}
	if (pthread_create(&prog->monitor_thread, NULL, monitor,
			prog) != 0)
		return ;
	return ;
}
