/*
** philosophers.h for Philosopher in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/includes
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Sun Mar 19 11:27:30 2017 Marwane
** Last update Sun Mar 19 12:34:53 2017 Marwane
*/

#ifndef _PHILOSOPHERS_H_
# define _PHILOSOPHERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define	LAST philosopher->lastAction
#define	BOWLS philosopher->table->bowls
#define	ID philosopher->id
#define	NBPHILOS philosopher->table->nbPhilos

typedef enum {
    UNDEFINED = -1,
    EAT = 0,
    THINK = 1,
    SLEEP = 2
}      Action;

typedef struct		s_table {
  int			nbPhilos;
  int			mealsLimit;
  bool			limitReached;
  pthread_cond_t	cond;
  pthread_barrier_t	barrier;
  pthread_mutex_t	*bowls;
}			t_table;

typedef struct		s_philo {
  int			id;
  int			nbMeals;
  int			timeToEat;
  int			timeToSleep;
  int			timeToThink;
  Action		lastAction;
  pthread_t		thread;
  struct s_table	*table;
}			t_philo;

void	philoThink(t_philo *philosopher);
void	philoEat(t_philo *philosopher);
void	philoSleep(t_philo *philosopher);
void	deleteTable(t_table *table);

bool	initPhilosopher(t_table *table, char **argv);
bool	checkParameters(char **argv);

#endif /* _PHILOSOPHERS_H_ */
