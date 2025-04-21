/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:55:49 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/21 14:54:44 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//MALLOC'd
//1.)prog->philos
//2.)prog->forks

void	free_exit(t_prog *prog, int code)
{
	int	i;

	if (prog->philos && prog->nop > 1)
	{
		i = -1;
		while (++i < prog->nop)
			pthread_join(prog->philos[i].t_id, NULL);
	}
	
	if (prog->forks)
	{
		i = -1;
		while (++i < prog->nop)
			pthread_mutex_destroy(&prog->forks[i]);
		free(prog->forks);
		//prog->forks = NULL;
	}
	if (prog->philos)
	{
		i = -1;
		while (++i < prog->nop)
			pthread_mutex_destroy(&prog->philos[i].meal_lock);
		free(prog->philos);
		//prog->philos = NULL;
	}
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	exit(code);
}

int	check_args(char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > P_MAX || is_notdigit(av[1]))
		return (write(2, "Invalid philo number\n", 21), 1);
	if (ft_atoi(av[2]) < 1 || is_notdigit(av[2]))
		return (write(2, "Invalid time to die\n", 20), 1);
	if (ft_atoi(av[3]) < 1 || is_notdigit(av[3]))
		return (write(2, "Invalid time to eat\n", 20), 1);
	if (ft_atoi(av[4]) < 1 || is_notdigit(av[4]))
		return (write(2, "Invalid time to sleep\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) < 1 || is_notdigit(av[5])))
		return (write(2, "Invalid meal number\n", 20), 1);
	return (0);
}

/*Check valgrind*/
int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac != 5 && ac != 6)
		return (write(2, "Wrong argument number\n", 22), 1);
	if (check_args(av))
		return (1);
	init_program(&prog, av);
	init_forks(&prog);
	init_philo(&prog);
	dinner_start(&prog);
	free_exit(&prog, 0);
	return (0);
}
