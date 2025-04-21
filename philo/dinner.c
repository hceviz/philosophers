/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 11:37:04 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/21 15:10:15 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(t_prog *prog)
{
	int	i;

	while (!someone_dead(prog))
	{
		i = -1;
		while (++i < prog->nop)
		{
			pthread_mutex_lock(&prog->philos[i].meal_lock);
			if ((gettime() - prog->philos[i].lastmeal_time) > prog->time_to_die)
			{
				pthread_mutex_unlock(&prog->philos[i].meal_lock);
				write_status((gettime() - prog->start_time), prog->philos[i].id,
					'd', prog);
				pthread_mutex_lock(&prog->dead_lock);
				prog->someone_dead = true;
				pthread_mutex_unlock(&prog->dead_lock);
				break;
			}
			pthread_mutex_unlock(&prog->philos[i].meal_lock);
			if (prog->finished_count >= prog->nop)
				free_exit(prog, 0);
		}
	}
	return (NULL);
}

void	write_status(long time, int philo_id, char op, t_prog *prog)
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
	if (someone_dead(prog) && op != 'd') //modified
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
		usleep(100);
	while (1)
	{
		if (someone_dead(philo->prog)) //new
			break;
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->prog->meal_num > 0 && philo->finished)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			break;
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

	prog->start_time = gettime();
	if (prog->nop == 1)
		onephilo(&prog->philos[0]); 
	i = -1;
	while (++i < prog->nop)
		prog->philos[i].lastmeal_time = prog->start_time;
	i = -1;
	while (++i < prog->nop)
	{
		if (pthread_create(&prog->philos[i].t_id, NULL,
				routine, &prog->philos[i]) != 0)
			break;
	}
	//usleep(20);
	monitor(prog);
	/* pthread_join(prog->monitor_thread, NULL);
	i = -1;
	while (++i < prog->nop)
	{
		if (pthread_join(prog->philos[i].t_id, NULL) != 0)
			free_exit(prog, 1);
	} */
	return ;
	
}
