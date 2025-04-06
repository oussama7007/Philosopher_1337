/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:56:43 by oait-si-          #+#    #+#             */
/*   Updated: 2025/04/06 01:45:14 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <string.h>
int main(int ac, char **av)
{
    t_philo  philo;
    write(1, "please enter the number of philosofers\n",32);
    philo.number_of_philosophers = atoi(av[1]);
        write(1, "please enter the number of philosofers\n",32);

}