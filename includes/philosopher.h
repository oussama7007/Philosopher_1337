
#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	unsigned int			id;
	unsigned int 		meals_eaten;
	size_t				last_meal;
	pthread_t			thread;
	struct s_prosses	    *program;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}		t_philo ;

typedef struct s_prosses
{
    unsigned int N_philos;
    unsigned int T_die;
    unsigned int T_eat;
    unsigned int T_sleep;
    int          N_must_eat;
    pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
    pthread_mutex_t  *forks;
    unsigned int    start_time;
    t_philo *philos;
} t_prosses;



//Simulate eating for T_eat milliseconds
//usleep(program->time_to_eat * 1000);



//The is_valid function checks if a number exceeds 2147483647 (max int), but your variables are unsigned int (max 4294967295). This mismatch could allow values up to 4294967295, which may not align with project intent if a lower limit is expected
#endif 