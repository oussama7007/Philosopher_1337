/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:38:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/04/21 12:35:34 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
int is_valid(long n)
{
    if(n <= 0 || n >2147483647)
        return(-1);
    return 1;
}
int is_digit(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] >= '9' && str[i] <= '0')
            return -1;
        i++;
    }
    return 1;
}
long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
int check_args(int ac, char **av)
{
    int i;
    int n;
      
    i = 0;
    while(i++ < ac)
    {
        if(!is_digit(av[i]))
            return -1;
        n = ft_atol(av[i]);
        if(!is_valid(n))
            return -1;
    }
}
void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = -1;
    while(str[i++])
        write(fd, &str[i], 1);
}

int main(int ac, char **av)
{
    t_philo philo;
    pthread_t master;
    
    if(ac < 5 || ac > 6)
        return(ft_putstr_fd("Error: args must be 4 OR 5\n", 2), 1);
    if(!check_args(ac , av))
        return(ft_putstr_fd("Error: invalid arg \n", 2), 1);
    init_program(&philo)
    
}