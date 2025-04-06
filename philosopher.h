/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:57:28 by oait-si-          #+#    #+#             */
/*   Updated: 2025/04/06 00:40:11 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef  PHILOSOFER_H
#define PHILOSOFER_H

#include <unistd.h>

typedef struct s_philo
{
    size_t number_of_philosophers;
    size_t time_to_eat;
    size_t number_of_times_each_philosopher_must_eat;
    size_t time_to_sleep;
    size_t time_to_die;
    
} t_philo;


#endif 