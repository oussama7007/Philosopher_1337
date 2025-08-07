

// # ifndef PHILO_BONUS
// #define PHILO_BONUS


// # include <stdio.h>
// # include <unistd.h>
// # include <string.h>
// # include <pthread.h>
// # include <stdlib.h>
// # include <sys/time.h>



// typedef struct s_process
// {
    
// }t_process;


// #endif 


#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

// Forward declaration
struct s_process;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal;
    pid_t           pid;
    pthread_t       monitor_thread;
    struct s_process *program;
    sem_t   *meal_sem;
} t_philo;

typedef struct s_process
{
    int             N_philos;
    long long       T_die;
    long long       T_eat;
    long long       T_sleep;
    long long       N_must_eat;
    int             all_ate;
    int             dead_flag;
    sem_t           *forks_sem;
    sem_t           *write_sem;
    sem_t           *dead_sem;
    sem_t           *meal_check_sem;
    long long       start_time;
    t_philo         *philos;
} t_process;

// Function prototypes
// Time functions
long long   get_current_time(void);
void        ft_usleep(long long time_needed, t_process *program);

// Initialization
int         init_program(t_process *program, int ac, char **av);
int         init_semaphores(t_process *program);
int         init_philosophers(t_process *program);

// Utils
long long   ft_atol(const char *str);
int         is_digit(char *str);
int         is_valid(long long n);
void        ft_putstr_fd(char *str, int fd);

// Process functions
int         create_processes(t_process *program);
void        philosopher_routine(t_philo *philo);
void        *death_monitor(void *arg);

// Cleanup
void        clean_up(t_process *program);

#endif