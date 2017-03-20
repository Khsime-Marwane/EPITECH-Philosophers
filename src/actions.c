/*
** actions.c for actions in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Fri Mar 17 01:03:58 2017 Marwane
** Last update Sun Mar 19 12:18:48 2017 Marwane
*/

#include "../includes/extern.h"
#include "../includes/philosophers.h"

void	philoThink(t_philo *philosopher) {
  int whichChopstick;

  if ((whichChopstick = 0 && LAST != THINK &&
       pthread_mutex_trylock(&BOWLS[ID]) == 0) ||
      (whichChopstick = 1 && LAST != THINK &&
       pthread_mutex_trylock(&BOWLS[(ID + 1) % NBPHILOS]) == 0))
    {

    lphilo_take_chopstick(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    lphilo_think();

    LAST = THINK;

    pthread_mutex_unlock(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    lphilo_release_chopstick(&BOWLS[(ID + whichChopstick) % NBPHILOS]);
    usleep(philosopher->timeToThink);
  }
}

static void	resetStick(t_philo *philosopher, int opt)
{
  if (opt == 0)
  {
    lphilo_take_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
    pthread_mutex_unlock(&BOWLS[(ID + 1) % NBPHILOS]);
    lphilo_release_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
    return ;
  }
  if (opt == 1)
  {
    lphilo_take_chopstick(&BOWLS[ID]);
    pthread_mutex_unlock(&BOWLS[ID]);
    lphilo_release_chopstick(&BOWLS[ID]);
    return ;
  }
}

void	philoEat(t_philo *philosopher)
{
  int	right;
  int	left;

  if ((right = pthread_mutex_trylock(&BOWLS[(ID + 1) % NBPHILOS])) == 0 &&
      (left = pthread_mutex_trylock(&BOWLS[ID])) == 0)
    {
      lphilo_take_chopstick(&BOWLS[ID]);
      lphilo_take_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
      lphilo_eat();
      ++philosopher->nbMeals >= philosopher->table->mealsLimit ?
	philosopher->table->limitReached = true : 0;
      LAST = EAT;
      pthread_mutex_unlock(&BOWLS[ID]);
      pthread_mutex_unlock(&BOWLS[(ID + 1) % NBPHILOS]);
      lphilo_release_chopstick(&BOWLS[ID]);
      lphilo_release_chopstick(&BOWLS[(ID + 1) % NBPHILOS]);
      usleep(philosopher->timeToThink);
    }
  else
    {
      if (right == 0)
	resetStick(philosopher, 0);
      if (left == 0)
	resetStick(philosopher, 1);
    }
}

void	philoSleep(t_philo *philosopher)
{
  lphilo_sleep();
  usleep(philosopher->timeToSleep);
  LAST = SLEEP;
}

bool	checkParameters(char **argv)
{
  if ((atoi(argv[2]) <= 0) ||
      (atoi(argv[4]) <= 0))
    return (false);
  if ((strcmp(argv[1], "-p") != 0) ||
      (strcmp(argv[3], "-e") != 0))
    return (false);
  return (true);
};
