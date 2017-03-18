/*
** actions.c for actions in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Fri Mar 17 01:03:58 2017 Marwane
** Last update Fri Mar 17 11:47:40 2017 Marwane
*/

#include "../includes/extern.h"
#include "../includes/philosophers.h"

#define LAST philosopher->lastAction
#define BOWLS philosopher->table->bowls
#define ID philosopher->id
#define NBPHILOS philosopher->table->nbPhilos

void	philoThink(t_philo *philosopher) {
  int whichChopstick;

  if ((whichChopstick = 0 && LAST != THINK && pthread_mutex_trylock(&BOWLS[ID]) == 0) ||
      (whichChopstick = 1 && LAST != THINK && pthread_mutex_trylock(&BOWLS[(ID + 1) % NBPHILOS]) == 0)) {

    lphilo_take_chopstick(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    lphilo_think();

    LAST = THINK;

    pthread_mutex_unlock(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    lphilo_release_chopstick(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    usleep(philosopher->timeToThink);
  }
}

void	philoEat(t_philo *philosopher) {
  int	right;
  int	left;

  if ((right = pthread_mutex_trylock(&BOWLS[(ID + 1) % NBPHILOS])) == 0 &&
      (left = pthread_mutex_trylock(&BOWLS[ID])) == 0) {

    lphilo_take_chopstick(&BOWLS[ID]);
    lphilo_take_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
    lphilo_eat();

    ++philosopher->nbMeals >= philosopher->table->mealsLimit ? philosopher->table->limitReached = true : 0;
    LAST = EAT;

    pthread_mutex_unlock(&BOWLS[ID]);
    pthread_mutex_unlock(&BOWLS[(ID + 1) % NBPHILOS]);
    lphilo_release_chopstick(&BOWLS[ID]);
    lphilo_release_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
    usleep(philosopher->timeToThink);
  }

  else {
    if (right == 0) {
      lphilo_take_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
      pthread_mutex_unlock(&BOWLS[(ID + 1) % NBPHILOS]);
      lphilo_release_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
    }
    if (left == 0) {
      lphilo_take_chopstick(&BOWLS[ID]);
      pthread_mutex_unlock(&BOWLS[ID]);
      lphilo_release_chopstick(&BOWLS[ID]);
    }
  }
}

void	philoSleep(t_philo *philosopher) {
  lphilo_sleep();
  usleep(philosopher->timeToSleep);
  LAST = SLEEP;
}
