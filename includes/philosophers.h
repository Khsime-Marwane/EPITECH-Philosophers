//
// Author: Marwane Khsime 
// Date: 2017-03-16 20:02:17 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 20:02:17
//

#ifndef _PHILOSOPHERS_H_
# define _PHILOSOPHERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

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

#endif /* _PHILOSOPHERS_H_ */
