/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:38:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/04/23 22:49:00 by oait-si-         ###   ########.fr       */
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
        program->N_philos = ft_atou(av[1]);
        program->T_die = ft_atou(av[2]);
        program->T_eat = ft_atou(av[3]);
        program->T_sleep = ft_atou(av[4]);
        if(ac == 5)
            program->N_must_eat = -1;
        else 
            program->N_must_eat = ft_atou(av[4]);

}
int     allocate_resources(t_prosses *program)
{
    program->fork = malloc(sizeof(pthread_mutex_t) * program->N_philos);
    if(!program->fork)
        return 0;
    program->philos = malloc(sizeof(t_philo) * program->N_philos);
    if(!program->philos)
        return 0;
}
int init_mutexs(t_prosses *program)
{
    // if(pthread_mutex_init(&program->write_lock, NULL) != 0)
    //     return(0);
    // if(pthread_mutex_init(&program->dead_lock, NULL) != 0)
    // {
    //     pthread_mutex_destroy(&program->write_lock, NULL);
            //return (1);
    // }
    
}
int init_program(t_prosses *program, int ac, char **av)
{
    assigning_values(&program, ac, av);
    if(!allocate_resources(&program) != 1)
        return(ft_putstr_fd("Error: allocation failed\n", 2), 0);
    if(!(init_mutexs(program)))
    {
        free(program->philos);
        free(program->fork);
        return(ft_putstr_fd("Error: initialisation of mutexs failed\n", 2), 0);
    }
    init_philo(program);
    return(1)
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
    if(!(creatr_philos_threads(&program))
}