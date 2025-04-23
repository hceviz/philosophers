/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:15:38 by hceviz            #+#    #+#             */
/*   Updated: 2025/04/23 14:19:17 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

# define P_MAX 200

typedef struct s_philo	t_philo;

typedef struct s_prog
{
	bool			someone_dead;
	int				nop;
	int				meal_num;
	int				finished_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			s_time;
	pthread_t		monitor_thread;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_prog;

typedef struct s_philo
{
	pthread_t		t_id;
	int				id;
	int				meal_count;
	int				finished;
	size_t			lastmeal_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	meal_lock;
	t_prog			*prog;
}	t_philo;

//utils.c
int		ft_atoi(char *c);
void	ft_exit(char *msg);
int		is_notdigit(char *av);
void	precise_sleep(t_prog *prog, long ms);
bool	someone_dead(t_prog *prog);

//main.c
void	free_exit(t_prog *prog, int code);
long	gettime(void);

//init.c
void	init_program(t_prog *prog, char **av);
void	init_forks(t_prog *prog);
void	init_philo(t_prog *prog);

//dinner.c
void	write_stat(long time, int philo_id, char op, t_prog *prog);
void	dinner_start(t_prog *prog);

//ops.c
void	eat(t_philo *philo);
void	philosleep(t_philo *philo);
void	think(t_philo *philo);
void	onephilo(t_philo *philo);
#endif