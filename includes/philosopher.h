
#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct s_philo
{
	// unsigned int 					id;
	// unsigned int 					meals_eaten;
	// size_t				last_meal;
	// pthread_t			thread;
	// struct s_prosses	*program;
	// pthread_mutex_t		*r_fork;
	// pthread_mutex_t		*l_fork;
}		t_philo ;

typedef struct s_prosses
{
    unsigned int N_philos;
    unsigned int T_die;
    unsigned int T_eat;
    unsigned int T_sleep;
    unsigned int N_must_eat;
    pthread_mutex_t  *fork;
    t_philo *philos;
} t_prosses;

#endif 