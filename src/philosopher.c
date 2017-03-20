/*
** philosopher.c for philosopher in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Sun Mar 19 12:19:56 2017 Marwane
** Last update Sun Mar 19 13:14:25 2017 Sébastien Jacobin
*/

#include "extern.h"
#include "philosophers.h"

static	bool		waitForPhilosophers(t_table *table,
					    t_philo *philosophers)
{
  int			i;

  i = 0;
  while (i < table->nbPhilos)
    {
      if (pthread_join(philosophers[i++].thread, NULL) != 0)
	return (false);
    }
  return (true);
}

static	void		*philosopherAlgorithm(void *_philosopher)
{
  t_philo		*philosopher;

  philosopher = (t_philo *)_philosopher;
  pthread_barrier_wait(&philosopher->table->barrier);
  while (!philosopher->table->limitReached ||
	 philosopher->nbMeals < philosopher->table->mealsLimit)
    {
      if (philosopher->lastAction == UNDEFINED ||
	  philosopher->lastAction == SLEEP)
	philoThink(philosopher);

      else if (philosopher->lastAction == UNDEFINED ||
	       philosopher->lastAction == THINK)
	philoEat(philosopher);

      else
	philoSleep(philosopher);
    }
  pthread_exit(NULL);
}

static bool	runPhilosopher(t_table *table, t_philo *philosophers, int i)
{
  philosophers[i].id = i;
  philosophers[i].nbMeals = 0;
  philosophers[i].lastAction = UNDEFINED;
  philosophers[i].table = table;
  philosophers[i].timeToEat = 100;
  philosophers[i].timeToSleep = 100;
  philosophers[i].timeToThink = 100;
  if (pthread_create(&philosophers[i].thread, NULL,
		     &philosopherAlgorithm, &philosophers[i]) != 0)
    return (false);
  return (true);
}

static bool		runPhilosophers(t_table *table)
{
  pthread_mutex_t	_bowls[table->nbPhilos];
  t_philo		philosophers[table->nbPhilos];
  int			i;

  table->bowls = _bowls;
  i = 0;
  while (i < table->nbPhilos)
    if (pthread_mutex_init(&table->bowls[i++], NULL) != 0)
      return (false);
  if (pthread_barrier_init(&table->barrier, NULL, table->nbPhilos) != 0)
    return (false);
  i = 0;
  while (i < table->nbPhilos)
    {
      if (runPhilosopher(table, philosophers, i) == false)
	return (false);
      i++;
    }
  if (!waitForPhilosophers(table, philosophers))
    return (false);
  return (true);
}

bool		initPhilosopher(t_table *table, char **argv)
{
  if (!checkParameters(argv))
    return (false);
  table->nbPhilos = atoi(argv[2]);
  table->mealsLimit = atoi(argv[4]);
  table->limitReached = (false);
  if (pthread_cond_init(&table->cond, NULL) != 0)
    return (false);
  if (table->nbPhilos <= 1)
    return (false);
  return (runPhilosophers(table));
}
