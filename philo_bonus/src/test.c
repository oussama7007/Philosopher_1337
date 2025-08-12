/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:48:33 by oait-si-          #+#    #+#             */
/*   Updated: 2025/08/12 20:16:48 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strcat(char *dest, const char *src)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    while (dest[i] != '\0')
        i++;
    j = 0;
    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}

char *ft_strcpy(char *dst, const char *src)
{
    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

static int get_length(int n)
{
    int len;

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

static char *negative(int len, char *str, unsigned int num)
{
    while (len > 0)
    {
        str[len--] = (num % 10) + '0';
        num /= 10;
    }
    return (str);
}

static char *positive(int len, char *str, unsigned int num)
{
    while (len >= 0)
    {
        str[len--] = (num % 10) + '0';
        num /= 10;
    }
    return (str);
}

static char *alloc(int len)
{
    char *str;

    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    return (str);
}

char *ft_itoa(int n)
{
    char *str;
    int len;
    unsigned int num;
    char *tmp;

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

long long ft_atol(const char *str)
{
    long long res;
    int i;

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

int is_digit(char *str)
{
    int i;

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

int is_valid(long long n)
{
    if (n < 0 || n > 2147483647)
        return (0);
    return (1);
}

void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
}

int check_args(int ac, char **av)
{
    int i;

    if (ac < 5 || ac > 6)
    {
        ft_putstr_fd("Error: args must be 4 or 5\n", 2);
        return (0);
    }
    if (ft_atol(av[1]) <= 0)
    {
        ft_putstr_fd("Error: invalid number of philosophers\n", 2);
        return (0);
    }
    i = 1;
    while (++i < ac)
    {
        if (!is_digit(av[i]) || !is_valid(ft_atol(av[i])))
        {
            ft_putstr_fd("Error: invalid argument\n", 2);
            return (0);
        }
    }
    // Check positive times
    if (ft_atol(av[2]) <= 0 || ft_atol(av[3]) <= 0 || ft_atol(av[4]) <= 0)
    {
        ft_putstr_fd("Error: time arguments must be positive integers\n", 2);
        return (0);
    }
    return (1);
}

long long get_current_time(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
    {
        ft_putstr_fd("Error: gettimeofday failed\n", 2);
        return (-1);
    }
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long long time_needed, t_process *program)
{
    long long start_time;
    long long current;

    start_time = get_current_time();
    if (start_time == -1)
        return;
    while (1)
    {
        current = get_current_time();
        if (current == -1 || (current - start_time >= time_needed))
            break;
        usleep(100);
    }
}

void print_philo_status(t_philo *philo, char *string)
{
    long long timestamp;

    sem_wait(philo->program->write_sem);
    timestamp = get_current_time() - philo->program->start_time;
    if (timestamp == -1)
    {
        sem_post(philo->program->write_sem);
        return;
    }
    printf("[%lld] %d %s\n", timestamp, philo->id, string);
    sem_post(philo->program->write_sem);
}

void philo_eat(t_philo *philo)
{
    t_process *program = philo->program;
    long long now;

    if (program->n_philos > 1)
        sem_wait(program->room_sem);
    sem_wait(program->forks_sem);
    print_philo_status(philo, "has taken a fork");
    sem_wait(program->forks_sem);
    print_philo_status(philo, "has taken a fork");
    sem_wait(philo->meal_sem);
    now = get_current_time();
    if (now == -1)
    {
        sem_post(philo->meal_sem);
        return;
    }
    philo->last_meal = now;
    philo->meals_eaten++;
    sem_post(philo->meal_sem);
    print_philo_status(philo, "is eating");
    ft_usleep(program->t_eat, program);
    sem_post(program->forks_sem);
    sem_post(program->forks_sem);
    if (program->n_philos > 1)
        sem_post(program->room_sem);
}

void philo_sleep(t_philo *philo)
{
    print_philo_status(philo, "is sleeping");
    ft_usleep(philo->program->t_sleep, philo->program);
}

void philo_think(t_philo *philo)
{
    print_philo_status(philo, "is thinking");
}

int assigning_values(t_process *program, int ac, char **av)
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
        return (0);
    return (1);
}

int init_semaphores(t_process *program)
{
    sem_unlink("/forks");
    sem_unlink("/write");
    sem_unlink("/room");
    program->forks_sem = sem_open("/forks", O_CREAT, 0644, program->n_philos);
    program->write_sem = sem_open("/write", O_CREAT, 0644, 1);
    program->room_sem = sem_open("/room", O_CREAT, 0644, program->n_philos - 1);
    if (program->forks_sem == SEM_FAILED || program->write_sem == SEM_FAILED || program->room_sem == SEM_FAILED)
    {
        ft_putstr_fd("Error: semaphore creation failed\n", 2);
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
        ft_putstr_fd("Error: malloc failed\n", 2);
        return (0);
    }
    i = -1;
    while (++i < program->n_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = program->start_time;
        program->philos[i].program = program;
        program->philos[i].pid = -1;
    }
    return (1);
}

int init_program(t_process *program, int ac, char **av)
{
    if (!assigning_values(program, ac, av))
        return (0);
    if (!init_semaphores(program))
        return (0);
    if (!init_philosophers(program))
        return (0);
    return (1);
}

void *death_monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_process *program = philo->program;
    long long current;

    while (1)
    {
        sem_wait(philo->meal_sem);
        current = get_current_time();
        if (current == -1)
        {
            sem_post(philo->meal_sem);
            return (NULL);
        }
        if (current - philo->last_meal >= program->t_die)
        {
            print_philo_status(philo, "died");
            exit(1);
        }
        sem_post(philo->meal_sem);
        usleep(10);  // Tighter sleep for precision
    }
    return (NULL);
}

void philosopher_routine(t_philo *philo)
{
    t_process *program = philo->program;
    char *pid_str;
    char sem_name[50];

    pid_str = ft_itoa(getpid());
    if (!pid_str)
    {
        ft_putstr_fd("Error: ft_itoa failed\n", 2);
        exit(1);
    }
    ft_strcpy(sem_name, "/philo_meal_sem_");
    ft_strcat(sem_name, pid_str);
    free(pid_str);  
    sem_unlink(sem_name);
    philo->meal_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
    if (philo->meal_sem == SEM_FAILED)
    {
        ft_putstr_fd("Error: semaphore creation failed\n", 2);
        exit(1);
    }
    sem_wait(philo->meal_sem);
    philo->last_meal = get_current_time();
    sem_post(philo->meal_sem);
    if (pthread_create(&philo->monitor_thread, NULL, death_monitor, philo) != 0)
    {
        ft_putstr_fd("Error: Failed to create monitor thread\n", 2);
        sem_close(philo->meal_sem);
        sem_unlink(sem_name);
        exit(1);
    }
    pthread_detach(philo->monitor_thread);  // Detach to avoid join issues
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
    sem_close(philo->meal_sem);
    sem_unlink(sem_name);
    exit(0);
}

int create_processes(t_process *program)
{
    int i;
    pid_t pid;

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
            program->philos[i].id = i + 1;  // Ensure ID set in child
            philosopher_routine(&program->philos[i]);
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
    sem_close(program->room_sem);
    sem_unlink("/forks");
    sem_unlink("/write");
    sem_unlink("/room");
    if (program->philos)
        free(program->philos);
}

void wait_for_processes(t_process *program)
{
    int status;
    pid_t waited_pid;

    while (1)
    {
        waited_pid = waitpid(-1, &status, 0);
        if (waited_pid <= 0)
            break;
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 1)
            {
                // Death occurred, kill others
                int j = -1;
                while (++j < program->n_philos)
                {
                    if (program->philos[j].pid > 0 && program->philos[j].pid != waited_pid)
                        kill(program->philos[j].pid, SIGKILL);
                }
                break;
            }
            else if (WEXITSTATUS(status) == 0)
            {
                program->all_ate++;
                if (program->all_ate == program->n_philos)
                    break;
            }
        }
        // Continue waiting for killed processes (SIGKILL status ignored)
    }
}

int main(int ac, char **av)
{
    t_process program;

    if (!check_args(ac, av))
        return (1);
    if (!init_program(&program, ac, av))
        return (1);
    if (!create_processes(&program))
    {
        clean_up(&program);
        return (1);
    }
    wait_for_processes(&program);
    clean_up(&program);
    return (0);
}