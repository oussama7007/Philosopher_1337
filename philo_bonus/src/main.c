/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:48:33 by oait-si-          #+#    #+#             */
/*   Updated: 2025/08/01 16:39:13 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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


int     check_args(int ac , char **av)
{
    if(ac > 5 || ac < 4)
    {
        ft_putstr_fd("Error: args must be 4 OR 5", 2);
        return(0);
    }
    int i = 0;
	while (++i < ac)
	{
		if (!is_digit(av[i]) || !is_valid(ft_atol(av[i])))
		{
			ft_putstr_fd("Error: invalid arg", 2);
			return (0);
		}
	}
	return (1);
}


int main(int ac, char **av)
{
    if(!check_args(ac , av))
        return 1;
		
}