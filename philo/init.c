/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:48:57 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/23 11:59:45 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_prog *prog, char **av)
{
	memset(prog, 0, sizeof(t_prog));
	prog->nop = ft_atoi(av[1]);
	prog->time_to_die = ft_atoi(av[2]);
	prog->time_to_eat = ft_atoi(av[3]);
	prog->time_to_sleep = ft_atoi(av[4]);
	prog->meal_num = -1;
	if (av[5])
		prog->meal_num = ft_atoi(av[5]);
	prog->someone_dead = false;
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
}

void	init_forks(t_prog *prog)
{
	int	i;

	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->nop);
	if (!prog->forks)
		ft_exit("Malloc error");
	i = -1;
	while (++i < prog->nop)
		pthread_mutex_init(&prog->forks[i], NULL);
}

void	assign_forks(t_prog *prog, int pos)
{
	t_philo	*philo;

	philo = &prog->philos[pos];
	philo->l_fork = &prog->forks[pos];
	philo->r_fork = &prog->forks[(pos + 1) % prog->nop];
}

void	init_philo(t_prog *prog)
{
	int	i;

	prog->philos = malloc(sizeof(t_philo) * prog->nop);
	if (!prog->philos)
		ft_exit("Malloc error");
	i = -1;
	while (++i < prog->nop)
	{
		prog->philos[i].id = i + 1;
		prog->philos[i].lastmeal_time = 0;
		prog->philos[i].prog = prog;
		prog->philos[i].finished = 0;
		prog->philos[i].meal_count = 0;
		pthread_mutex_init(&prog->philos[i].meal_lock, NULL);
		assign_forks(prog, i);
	}
}
