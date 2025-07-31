/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:38:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/07/31 00:33:14 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




// #include "../includes/philosopher.h"

// void	clean_up(t_process *resources)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < resources->N_philos)
// 		pthread_mutex_destroy(&resources->forks[i]);
// 	pthread_mutex_destroy(&resources->write_lock);
// 	pthread_mutex_destroy(&resources->dead_lock);
// 	free(resources->forks);
// 	free(resources->philos);
// }

// int	is_valid(long long n)
// {
// 	if (n <= 0 || n > 2147483647)
// 		return (0);
// 	return (1);
// }
// int is_digit(char *str)
// {
//     int i;

//     i = 0;
//     while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
//         i++;
//     if(str[i] == '-' || str[i] == '+')
//     {
//         if(str[i] == '-')
//             return 0;
//         i++;
//     }
//     while(str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
//     {
//         if(str[i] > '9' || str[i] < '0')
//             return 0;
//         i++;
//     }
//     while(str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
//         i++;
//     if(str[i] != '\0')
//         return 0;
 
//     return 1;
// }
// long long	ft_atol(const char *str)
// {
// 	long long	res;
// 	int			i;

// 	res = 0;
// 	i = 0;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '+')
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = res * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	return (res);
// }
// int check_args(int ac, char **av)
// {
//     int i;
      
//     i = 0;
//     while(++i < ac)
//     {
//         if(is_digit(av[i]) != 1)
//             return 0;
//         if(is_valid(ft_atol(av[i])) != 1)
//             return 0;
        
//     }
//     return 1;
// }
// void ft_putstr_fd(char *str, int fd)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         write(fd, &str[i], 1);
//         i++;
        
//     }
// }

// long long	get_current_time(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		return (-1);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }
// // void    ft_usleep(long long time_needed, t_process *process)
// // {
// //     long long  start_time;
// // 	if(process->dead_flag)
// // 	{
// // 		clean_up(process);
// // 		exit(0);
// // 	}
// // 	start_time = get_current_time();
// //     while(get_current_time() - start_time <  time_needed)
// //         usleep(10);
// // }
// void    ft_usleep(long long time_needed)
// {
//     long long  start_time;
	
// 	start_time = get_current_time();
//     while(get_current_time() - start_time <  time_needed)
//         usleep(50);
// }
// int	assigning_values(t_process *program, int ac, char **av)
// {
// 	program->N_philos = ft_atol(av[1]);
// 	program->T_die = ft_atol(av[2]);
// 	program->T_eat = ft_atol(av[3]);
// 	program->T_sleep = ft_atol(av[4]);
// 	program->dead_flag = 0;
// 	program->all_philos_eat = 0;
// 	if (ac == 6)
// 		program->N_must_eat = ft_atol(av[5]);
// 	else
// 		program->N_must_eat = -1;
// 	program->start_time = get_current_time();
// 	if (program->start_time < 0)
// 		return (ft_putstr_fd("gettimeofday failed\n", 2), 0);
// 	return (1);
// }

// int	allocate_resources(t_process *program)
// {
// 	program->forks = malloc(sizeof(pthread_mutex_t) * program->N_philos);
// 	if (!program->forks)
// 		return (0);
// 	program->philos = malloc(sizeof(t_philo) * program->N_philos);
// 	if (!program->philos)
// 		return (free(program->forks), 0);
// 	return (1);
// }

// int	init_mutexs(t_process *program)
// {
// 	int	i;

// 	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
// 		return (0);
// 	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
// 	{
// 		pthread_mutex_destroy(&program->write_lock);
// 		return (0);
// 	}
// 	i = -1;
// 	while (++i < program->N_philos)
// 	{
// 		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
// 		{
// 			while (--i >= 0)
// 				pthread_mutex_destroy(&program->forks[i]);
// 			pthread_mutex_destroy(&program->write_lock);
// 			pthread_mutex_destroy(&program->dead_lock);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// void	init_philo(t_process *program)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < program->N_philos)
// 	{
// 		program->philos[i].id = i + 1;
// 		program->philos[i].meals_eaten = 0;
// 		program->philos[i].last_meal = program->start_time;
// 		program->philos[i].r_fork = &program->forks[i];
// 		program->philos[i].l_fork = &program->forks[(i + 1) % program->N_philos];
// 		program->philos[i].program = program;
// 	}
// }

// int	init_program(t_process *program, int ac, char **av)
// {
// 	if (assigning_values(program, ac, av) != 1 || allocate_resources(program) != 1)
// 		return (ft_putstr_fd("Error: allocation failed\n", 2), 0);
// 	if (!(init_mutexs(program)))
// 	{
// 		free(program->philos);
// 		free(program->forks);
// 		return (ft_putstr_fd("Error: initialisation of mutexs failed\n", 2), 0);
// 	}
// 	init_philo(program);
// 	return (1);
// }

// void	print_philo_status(t_philo *philo, char *string)
// {
// 	t_process	*process_status;

// 	long long 	timestamp;
// 	process_status = philo->program;
	
// 	pthread_mutex_lock(&process_status->dead_lock);
// 	if (!process_status->dead_flag && !process_status->all_philos_eat)
// 	{
// 		timestamp = get_current_time() - philo->program->start_time;
// 		pthread_mutex_lock(&process_status->write_lock);
// 		printf("%lld %d %s\n", timestamp, philo->id, string);
// 		pthread_mutex_unlock(&process_status->write_lock);
// 	}
// 	pthread_mutex_unlock(&process_status->dead_lock);
// }

// void	philo_eat(t_philo *philo)
// {
// 	t_process	*eat_process;

// 	eat_process = philo->program;
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->l_fork);
// 		print_philo_status(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->r_fork);
// 		print_philo_status(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->r_fork);
// 		print_philo_status(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->l_fork);
// 		print_philo_status(philo, "has taken a fork");
// 	}
// 	pthread_mutex_lock(&eat_process->dead_lock);
// 	philo->last_meal = get_current_time();
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&eat_process->dead_lock);
// 	print_philo_status(philo, "is eating");
// 	ft_usleep(eat_process->T_eat);//ft_usleep(eat_process->T_eat, eat_process );//usleep(eat_process->T_eat * 1000);
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }

// void	philo_think(t_philo *philo)
// {
// 	print_philo_status(philo, "is thinking");
// 	 long long think_time = philo->program->T_die - (get_current_time() - philo->last_meal) - philo->program->T_eat;
//     if (think_time < 0)
//         think_time = 0;
//     ft_usleep(think_time * 0.42);
// }

// void	philo_sleep(t_philo *philo, t_process *process)
// {
// 	print_philo_status(philo, "is sleeping");
// 	ft_usleep(philo->program->T_sleep);//ft_usleep(philo->program->T_sleep, process);
// }

// void	*philosopher_routine(void *arg)
// {
// 	t_philo		*philo;
// 	t_process	*program;

// 	philo = (t_philo *)arg;
// 	program = philo->program;
// 	if (philo->id % 2 == 0)
// 		ft_usleep(1);// ft_usleep(1, program);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&program->dead_lock);
// 		if (program->dead_flag || program->all_philos_eat)
// 		{
// 			pthread_mutex_unlock(&program->dead_lock);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&program->dead_lock);
// 		philo_eat(philo);
		
// 		philo_sleep(philo, program);
// 		philo_think(philo);
// 	}
// 	return (NULL);
// }

// int	create_philos_threads(t_process *program)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < program->N_philos)
// 	{
// 		if (pthread_create(&program->philos[i].thread, NULL,
// 				philosopher_routine, &program->philos[i]) != 0)
// 			return (0);
// 	}
// 	return (1);
// }

// void	*master_routine(void *arg)
// {
// 	t_process	*master_progress;
// 	int			i;
// 	int			counter;

// 	master_progress = (t_process *)arg;
// 	while (1)
// 	{
// 		i = -1;
// 		counter = 0;
// 		while (++i < master_progress->N_philos)
// 		{
// 			pthread_mutex_lock(&master_progress->dead_lock);
// 			if (get_current_time() - master_progress->philos[i].last_meal > master_progress->T_die)
// 			{
// 				if(!master_progress->dead_flag)
// 				{
// 					master_progress->dead_flag = 1;
// 					pthread_mutex_unlock(&master_progress->dead_lock);
					
// 					pthread_mutex_lock(&master_progress->write_lock);
// 					// print_philo_status(&master_progress->philos[i], "is died");
// 					printf("%lld %d %s\n", get_current_time() - master_progress->start_time,
// 						master_progress->philos[i].id, "is died");
// 					pthread_mutex_unlock(&master_progress->write_lock);
// 					return NULL;
// 				}
// 			}
			
// 			if (master_progress->N_must_eat > 0
// 				&& master_progress->philos[i].meals_eaten >= master_progress->N_must_eat)
// 				counter++;
// 			pthread_mutex_unlock(&master_progress->dead_lock);
// 		}
// 		if (master_progress->N_must_eat > 0 && counter == master_progress->N_philos)
// 		{
// 			pthread_mutex_lock(&master_progress->dead_lock);
// 			master_progress->all_philos_eat = 1;
// 			pthread_mutex_unlock(&master_progress->dead_lock);
// 			return (NULL);
// 		}
	
// 		ft_usleep(1);//ft_usleep(1, master_progress);//usleep(1000);
// 	}
// 	return (NULL);
// }



// int	main(int ac, char **av)
// {
// 	t_process	program;
// 	pthread_t	master;
// 	int			i;

// 	if (ac < 5 || ac > 6)
// 		return (ft_putstr_fd("Error: args must be 4 OR 5\n", 2), 1);
// 	if (!check_args(ac, av))
// 		return (ft_putstr_fd("Error: invalid arg \n", 2), 1);
// 	if (!(init_program(&program, ac, av)))
// 		return (1);
// 	if (program.N_philos == 1)
// 	{
// 		printf("0 1 has taken a fork\n");
// 		ft_usleep(program.T_die);//ft_usleep(program.T_die, &program);//usleep(program.T_die * 1000);
// 		printf("%lld 1 is died\n", program.T_die);
// 		clean_up(&program);
// 		return (0);
// 	}
// 	if (!(create_philos_threads(&program)))
// 		return (1);
// 	if (pthread_create(&master, NULL, master_routine, &program) != 0)
// 	{
// 		ft_putstr_fd("Error: Failed to create master thread.\n", 2);
// 		return (1);
// 	}i = -1;
// 	while (++i < program.N_philos)
// 		pthread_join(program.philos[i].thread, NULL);
// 	pthread_join(master, NULL);
// 	clean_up(&program);
// 	return (0);
// }





#include "../includes/philosopher.h"

// =============================================================================
// UTILITY FUNCTIONS
// =============================================================================

void	clean_up(t_process *resources)
{
	int	i;

	i = -1;
	while (++i < resources->N_philos)
		pthread_mutex_destroy(&resources->forks[i]);
	pthread_mutex_destroy(&resources->write_lock);
	pthread_mutex_destroy(&resources->dead_lock);
	free(resources->forks);
	free(resources->philos);
}

int	is_valid(long long n)
{
	if (n <= 0 || n > 2147483647)
		return (0);
	return (1);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

long long	ft_atol(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (is_digit(av[i]) != 1)
			return (0);
		if (is_valid(ft_atol(av[i])) != 1)
			return (0);
	}
	return (1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// CRITICAL FIX: This is the new "interruptible" sleep function.
// It sleeps in small chunks (1ms) and checks the simulation status
// on each iteration. If a philosopher dies, this function will return
// early, allowing the thread to exit its main loop promptly.
void	ft_usleep(long long time_needed, t_process *program)
{
	long long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < time_needed)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag)
		{
			pthread_mutex_unlock(&program->dead_lock);
			return ; // Exit sleep early if simulation has ended
		}
		pthread_mutex_unlock(&program->dead_lock);
		usleep(1000); // Sleep for 1ms before checking again
	}
}

// =============================================================================
// INITIALIZATION FUNCTIONS
// =============================================================================

int	assigning_values(t_process *program, int ac, char **av)
{
	program->N_philos = ft_atol(av[1]);
	program->T_die = ft_atol(av[2]);
	program->T_eat = ft_atol(av[3]);
	program->T_sleep = ft_atol(av[4]);
	program->dead_flag = 0;
	program->all_philos_eat = 0;
	if (ac == 6)
		program->N_must_eat = ft_atol(av[5]);
	else
		program->N_must_eat = -1;
	program->start_time = get_current_time();
	if (program->start_time < 0)
		return (ft_putstr_fd("gettimeofday failed\n", 2), 0);
	return (1);
}

int	allocate_resources(t_process *program)
{
	program->forks = malloc(sizeof(pthread_mutex_t) * program->N_philos);
	if (!program->forks)
		return (0);
	program->philos = malloc(sizeof(t_philo) * program->N_philos);
	if (!program->philos)
		return (free(program->forks), 0);
	return (1);
}

int	init_mutexs(t_process *program)
{
	int	i;

	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&program->write_lock);
		return (0);
	}
	i = -1;
	while (++i < program->N_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&program->forks[i]);
			pthread_mutex_destroy(&program->write_lock);
			pthread_mutex_destroy(&program->dead_lock);
			return (0);
		}
	}
	return (1);
}

void	init_philo(t_process *program)
{
	int	i;

	i = -1;
	while (++i < program->N_philos)
	{
		program->philos[i].id = i + 1;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = program->start_time;
		program->philos[i].r_fork = &program->forks[i];
		program->philos[i].l_fork = &program->forks[(i + 1) % program->N_philos];
		program->philos[i].program = program;
	}
}

int	init_program(t_process *program, int ac, char **av)
{
	if (assigning_values(program, ac, av) != 1 || allocate_resources(program) != 1)
		return (ft_putstr_fd("Error: allocation failed\n", 2), 0);
	if (!(init_mutexs(program)))
	{
		free(program->philos);
		free(program->forks);
		return (ft_putstr_fd("Error: initialisation of mutexs failed\n", 2), 0);
	}
	init_philo(program);
	return (1);
}

// =============================================================================
// PHILOSOPHER ACTIONS
// =============================================================================

void	print_philo_status(t_philo *philo, char *string)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag && !philo->program->all_philos_eat)
	{
		pthread_mutex_lock(&philo->program->write_lock);
		timestamp = get_current_time() - philo->program->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, string);
		pthread_mutex_unlock(&philo->program->write_lock);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_philo_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_philo_status(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->program->dead_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_philo_status(philo, "is eating");
	// Use the new interruptible sleep
	ft_usleep(philo->program->T_eat, philo->program);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	// Use the new interruptible sleep
	ft_usleep(philo->program->T_sleep, philo->program);
}

void	philo_think(t_philo *philo)
{
	print_philo_status(philo, "is thinking");
}

// =============================================================================
// THREAD ROUTINES
// =============================================================================

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_process	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (philo->id % 2 == 0)
		ft_usleep(1, program);
	while (1)
	{
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag || program->all_philos_eat)
		{
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&program->dead_lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	create_philos_threads(t_process *program)
{
	int	i;

	i = -1;
	while (++i < program->N_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]) != 0)
		{
			ft_putstr_fd("Error: Failed to create thread.\n", 2);
			while (--i >= 0)
				pthread_join(program->philos[i].thread, NULL);
			return (0);
		}
	}
	return (1);
}

void	*master_routine(void *arg)
{
	t_process	*program;
	int			i;
	int			all_are_full;

	program = (t_process *)arg;
	while (1)
	{
		i = -1;
		all_are_full = 1;
		while (++i < program->N_philos)
		{
			pthread_mutex_lock(&program->dead_lock);
			if (get_current_time() - program->philos[i].last_meal > program->T_die)
			{
				if (!program->dead_flag)
				{
					program->dead_flag = 1;
					pthread_mutex_lock(&program->write_lock);
					printf("%lld %d %s\n", get_current_time()
						- program->start_time, program->philos[i].id, "is died");
					pthread_mutex_unlock(&program->write_lock);
				}
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			if (program->N_must_eat > 0
				&& program->philos[i].meals_eaten < program->N_must_eat)
				all_are_full = 0;
			pthread_mutex_unlock(&program->dead_lock);
		}
		if (program->N_must_eat > 0 && all_are_full)
		{
			pthread_mutex_lock(&program->dead_lock);
			program->all_philos_eat = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		// Use the interruptible sleep for the master thread as well
		ft_usleep(1, program);
	}
	return (NULL);
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int	main(int ac, char **av)
{
	t_process	program;
	pthread_t	master;
	int			i;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: args must be 4 OR 5\n", 2), 1);
	if (!check_args(ac, av))
		return (ft_putstr_fd("Error: invalid arg \n", 2), 1);
	if (ft_atol(av[1]) > 1000)
	{
		ft_putstr_fd("Error: Number of philosophers exceeds reasonable system limits (max 1000).\n", 2);
		return (1);
	}
	if (!(init_program(&program, ac, av)))
		return (1);
	if (program.N_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(program.T_die, &program);
		printf("%lld 1 is died\n", program.T_die);
		clean_up(&program);
		return (0);
	}
	if (!(create_philos_threads(&program)))
		return (clean_up(&program), 1);
	if (pthread_create(&master, NULL, master_routine, &program) != 0)
	{
		ft_putstr_fd("Error: Failed to create master thread.\n", 2);
		i = -1;
		while (++i < program.N_philos)
			pthread_join(program.philos[i].thread, NULL);
		return (clean_up(&program), 1);
	}
	i = -1;
	while (++i < program.N_philos)
		pthread_join(program.philos[i].thread, NULL);
	pthread_join(master, NULL);
	clean_up(&program);
	return (0);
}




////// test it with all 
/// rm all cm 
// try on bonus 