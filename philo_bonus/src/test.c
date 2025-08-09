/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:48:33 by oait-si-          #+#    #+#             */
/*   Updated: 2025/08/09 08:18:16 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
static int	get_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*negative(int len, char *str, unsigned int num)
{
	while (len > 0)
	{
		str[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static char	*positive(int len, char *str, unsigned int num)
{
	while (len >= 0)
	{
		str[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static	char	*alloc(int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;
	char			*tmp;

	len = get_length(n);
	str = alloc(len);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (n < 0)
		tmp = negative(len, str, num);
	else
		tmp = positive(len, str, num);
	return (tmp);
}
void	print_philo_status(t_philo *philo, char *string)
{
    long long	timestamp;

    sem_wait(philo->program->write_sem);
    timestamp = get_current_time() - philo->program->start_time;
    if(timestamp == -1)
    {
        // hndle what it should do whene it return -1
    }
    printf("[%lld] %d %s\n", timestamp, philo->id, string);
    sem_post(philo->program->write_sem);
}
void	philo_sleep(t_philo *philo)
{
    print_philo_status(philo, "is sleeping");
    ft_usleep(philo->program->t_sleep, philo->program);
}

void	philo_think(t_philo *philo)
{
    print_philo_status(philo, "is thinking");
}
long long	get_current_time(void)
{
    struct timeval	tv;

    if (gettimeofday(&tv, NULL))
        return (-1);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_needed, t_process *program)
{
    long long	start_time;

    start_time = get_current_time();
    while (get_current_time() - start_time < time_needed)
        usleep(100);
}
int	assigning_values(t_process *program, int ac, char **av)
{
    program->n_philos = ft_atol(av[1]);
    program->t_die = ft_atol(av[2]);
    program->t_eat = ft_atol(av[3]);
    program->t_sleep = ft_atol(av[4]);
   
    program->all_ate = 0;
    
    if (ac == 6)
        program->n_must_eat = ft_atol(av[5]);
    else
        program->n_must_eat = -1;
        
    program->start_time = get_current_time();
    if (program->start_time < 0)
    {
        ft_putstr_fd("Error: gettimeofday failed\n", 2);
        return (0);
    }
    return (1);
}

int	init_semaphores(t_process *program)
{
    program->forks_sem = sem_open("/forks", O_CREAT, 0644, program->n_philos);
    program->write_sem = sem_open("/write", O_CREAT, 0644, 1);
   
    

    if (program->forks_sem == SEM_FAILED || program->write_sem == SEM_FAILED  )
    {
        ft_putstr_fd("Error: semaphore initialization failed\n", 2);
        return (0);
    }
    return (1);
}

int init_philosophers(t_process *program)
{
    int i;
    
    program->philos = malloc(sizeof(t_philo) * program->n_philos);
    if (!program->philos)
    {
        ft_putstr_fd("Error: philosopher allocation failed\n", 2);
        return (0);
    }
    
    i = -1;
    while (++i < program->n_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = program->start_time;
        program->philos[i].program = program;
        program->philos[i].meal_sem = NULL;  // Set to NULL; initialized later
    }
    
    return (1);
}

void philo_eat(t_philo *philo)
{
    sem_wait(philo->program->forks_sem); // Take first fork
    print_philo_status(philo, "has taken a fork");
    sem_wait(philo->program->forks_sem); // Take second fork
    print_philo_status(philo, "has taken a fork");

    sem_wait(philo->meal_sem);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    sem_post(philo->meal_sem);
    
    print_philo_status(philo, "is eating");
    // Protect meal data
    
    ft_usleep(philo->program->t_eat, philo->program);

    sem_post(philo->program->forks_sem); // Release forks
    sem_post(philo->program->forks_sem);
}
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

int     check_args(int ac, char **av)
{
    int i;
    
    if(ac < 5 || ac > 6)
    {
        ft_putstr_fd("Error: args must be 4 OR 5\n", 2);
        return(0);
    }
    if (ft_atol(av[1]) > 1000)
    {
        ft_putstr_fd("Error: Number of philosophers exceeds reasonable system limits (max 1000).\n", 2);
        return (0);
    }
    i = 0;
    while (++i < ac)
    {
        if (!is_digit(av[i]) || !is_valid(ft_atol(av[i])))
        {
            ft_putstr_fd("Error: invalid argument\n", 2);
            return (0);
        }
    }
    return (1);
}
int	init_program(t_process *program, int ac, char **av)
{
    if (!assigning_values(program, ac, av))
        return (0);
        
    if (!init_semaphores(program))
        return (0);
        
    if (!init_philosophers(program))
    {
        sem_close(program->forks_sem);
        sem_close(program->write_sem);
       
        
        return (0);
    }
    
    return (1);
}

void *death_monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_process *program = philo->program;
    long long current_time;
    //int meals_eaten;

    while (1)
    {
       
        sem_wait(philo->meal_sem);
        current_time = get_current_time();
        
        if (current_time - philo->last_meal >= program->t_die)
        {
            sem_wait(program->write_sem);
            printf("[%lld] %d died\n", current_time - program->start_time, philo->id);
            exit(1);
        }
        
        if (program->n_must_eat != -1 && philo->meals_eaten >= program->n_must_eat)
        {
            sem_post(philo->meal_sem);
            exit(0);
        }
        sem_post(philo->meal_sem);
        //ft_usleep(1, program); // Small delay to avoid busy-waiting
        usleep(100);
    }
    return (NULL);
}


void philosopher_routine(t_philo *philo)
{
    t_process *program = philo->program;
    char      *pid_str;
    char      sem_name[50]; // Ensure buffer is large enough

    // 1. Convert the integer PID to a string
    pid_str = ft_itoa(getpid());
    if (!pid_str)
    {
        ft_putstr_fd("Error: ft_itoa memory allocation failed\n", 2);
        exit(1);
    }

    // 2. Manually concatenate strings to create the semaphore name
    strcpy(sem_name, "/philo_meal_sem_"); // Base name
    strcat(sem_name, pid_str);          // Append the PID string

    // Free the allocated string for the PID
    free(pid_str);

    // Unlink any previous semaphore with the same name before creating
    sem_unlink(sem_name);
    philo->meal_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
    if (philo->meal_sem == SEM_FAILED)
    {
        ft_putstr_fd("Error: semaphore creation failed\n", 2);
        exit(1);
    }
    
    // --- The rest of your routine ---
    sem_wait(philo->meal_sem);
    philo->last_meal = get_current_time();
    sem_post(philo->meal_sem);
    
    if (pthread_create(&philo->monitor_thread, NULL, death_monitor, philo) != 0)
    {
        ft_putstr_fd("Error: Failed to create monitor thread.\n", 2);
        sem_close(philo->meal_sem);
        sem_unlink(sem_name);
        free(pid_str);
        exit(1);
    }
    
    if (philo->id % 2 == 0)
        usleep(1000);
        
    while (1)
    {
        if (program->n_must_eat != -1 && philo->meals_eaten >= program->n_must_eat)
            break;
        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    free(pid_str); 
    pthread_join(philo->monitor_thread, NULL);
    sem_close(philo->meal_sem);
    sem_unlink(sem_name); // Clean up the semaphore
    exit(0);
}
int	create_processes(t_process *program)
{
    int		i;
    pid_t	pid;

    i = -1;
    while (++i < program->n_philos)
    {
        pid = fork();
        if (pid < 0)
        {
            ft_putstr_fd("Error: Fork failed\n", 2);
            return (0);
        }
        else if (pid == 0)
        {
            philosopher_routine(&program->philos[i]);
            exit(0);
        }
        else
        {
            program->philos[i].pid = pid;
        }
    }
    return (1);
}

void clean_up(t_process *program)
{
    int i;
    i = -1;
    while (++i < program->n_philos)
    {
        if (program->philos[i].pid > 0)
            kill(program->philos[i].pid, SIGKILL);
    }
    
    sem_close(program->forks_sem);
    sem_close(program->write_sem);
    sem_unlink("/forks");
    sem_unlink("/write");
    if(program->philos)
        free(program->philos);

}
void wait_for_processes(t_process *program)
{
    int i;
    int status;
    pid_t pid;
    
    while (1)
    {
        
        if (waitpid(-1, &status, 0) <= 0)
            break;
            
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            i = -1;
            while (++i < program->n_philos)
                if (program->philos[i].pid > 0 && program->philos[i].pid != pid)
                    kill(program->philos[i].pid, SIGKILL);
            break;
        }
        
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            program->all_ate++;
            if (program->all_ate == program->n_philos)
                break;
        }
    }
}

void f()
{
    system("leaks a.out");
}
int	main(int ac, char **av)
{
    t_process	program;
    
    if (!check_args(ac, av))
        return (1);
        
    if (!init_program(&program, ac, av))
        return (1);
        
    if (!create_processes(&program))
        return (clean_up(&program), 1);
        
    wait_for_processes(&program);
    clean_up(&program);
    
    return (0);
}