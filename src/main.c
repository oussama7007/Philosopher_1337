/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:38:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/05/02 23:19:30 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
int is_valid(unsigned int n)
{
    if(n == 0 ||  n > 2147483647)
        return(0);
    return 1;
}
int is_digit(char *str)
{
    int i;

    i = 0;
    while(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            return 0;
        i++;
    }
    while(str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
    {
        if(str[i] > '9' || str[i] < '0')
            return 0;
        i++;
    }
    while(str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
        i++;
    if(str[i] != '\0')
        return 0;
 
    return 1;
}
unsigned int	ft_atou(const char *str)
{
	unsigned int 	res;
	int		i;

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
int check_args(int ac, char **av)
{
    int i;
      
    i = 0;
    while(++i < ac)
    {
        if(is_digit(av[i]) != 1)
            return 0;
        if(is_valid(ft_atou(av[i])) != 1)
            return 0;
        
    }
    return 1;
}
void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while(str[i])
    {
        write(fd, &str[i], 1);
        i++;
        
    }
}
int     assigning_values(t_prosses *program, int ac, char **av)
{
        struct timeval tv;
        
        program->N_philos = ft_atou(av[1]);
        program->T_die = ft_atou(av[2]);
        program->T_eat = ft_atou(av[3]);
        program->T_sleep = ft_atou(av[4]);
        if(ac == 5)
            program->N_must_eat = 0;
        else 
            program->N_must_eat = ft_atou(av[4]);
        if(gettimeofday(&tv, NULL) != 0)
            return(ft_putstr_fd("gettimeofday failed\n:", 2), 0);
        program->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

}
int     allocate_resources(t_prosses *program)
{
    program->forks = malloc(sizeof(pthread_mutex_t) * program->N_philos);
    if(!program->forks)
        return 0;
    program->philos = malloc(sizeof(t_philo) * program->N_philos);
    if(!program->philos)
        return 0;
    return 1;
}
int init_mutexs(t_prosses *program)
{
    int i;
    if(pthread_mutex_init(&program->write_lock, NULL) != 0)
         return(0);
    if(pthread_mutex_init(&program->dead_lock, NULL) != 0)
    {
         pthread_mutex_destroy(&program->write_lock);
            return (0);
    }
    i = -1;
    while(++i < program->N_philos)
    {
        if(pthread_mutex_init(&program->forks[i], NULL) != 0)
        {
            while(--i >= 0)
                pthread_mutex_destroy(&program->forks[i]);
            pthread_mutex_destroy(&program->write_lock);
            pthread_mutex_destroy(&program->dead_lock);
            
            return(0);
        }
    }
    return 1;
}
void init_philo(t_prosses *program)
{
    int i;
    
    i = -1;
    while(++i < program->N_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = program->start_time;
        program->philos[i].r_fork = &program->forks[i];
        program->philos[i].l_fork = &program->forks[(i + 1) % program->N_philos];
    }
}
int init_program(t_prosses *program, int ac, char **av)
{
    if(allocate_resources(program) != 1 ||  assigning_values(program, ac, av) != 1)
        return(ft_putstr_fd("Error: allocation failed\n", 2), 0);
    if(!(init_mutexs(program)))
    {
        free(program->philos);
        free(program->forks);
        return(ft_putstr_fd("Error: initialisation of mutexs failed\n", 2), 0);
    }
    init_philo(program);
    return(1);
}
void    *philosopher_routine(void *arg)
{}
void    *monitor_routine(void *arg)
{
    
}
int     create_philos_treads(t_prosses *program , pthread_t *master)
{
    int i;
    i = -1;
    while(++i < program->N_philos)
    {
        if(pthread_create(&program->philos[i].thread, NULL, philosopher_routine, &program->philos[i]) != 0)
            return 0;
    }
    pthread_create(&master, NULL, monitor_routine,  )
}
int main(int ac, char **av)
{
    t_prosses program;
    pthread_t master;
    
    if(ac < 5 || ac > 6)
        return(ft_putstr_fd("Error: args must be 4 OR 5\n", 2), 1);
    if(!check_args(ac , av))
        return(ft_putstr_fd("Error: invalid arg \n", 2), 1);
    if(!(init_program(&program, ac, av)))
        return 1;
    if(!(create_philos_threads(&program, &master)))
         return 1;
}