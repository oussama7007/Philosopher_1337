
#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// typedef struct s_philo
// {
//     unsigned int       id;
//     unsigned int       meals_eaten;

//     pthread_mutex_t    l_fork;
//     pthread_mutex_t     r_fork;
// } t_philo;

typedef struct s_prosses
{
    unsigned int N_philos;
    unsigned int T_die;
    unsigned int T_eat;
    unsigned int T_sleep;
    unsigned int N_must_eat;
} t_prosses;

#endif 