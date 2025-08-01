#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

// Forward declaration to break the circular dependency between structs.
struct s_process;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	// CRITICAL FIX: Time variables must be long long to avoid overflow.
	long long			last_meal;
	pthread_t			thread;
	struct s_process	*program;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

// CRITICAL FIX: Renamed from t_prosses to t_process for consistency.
typedef struct s_process
{
	int 				N_philos;
	// CRITICAL FIX: Time variables must be long long to avoid overflow.
	long long			T_die;
	long long    		T_eat;
	long long			T_sleep;
	long long			N_must_eat;
	long long			all_philos_eat;
	int					dead_flag;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		*forks;
	// CRITICAL FIX: Time variables must be long long to avoid overflow.
	long long			start_time;
	t_philo				*philos;
}	t_process;

#endif