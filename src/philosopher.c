//
// Author: Marwane Khsime 
// Date: 2017-03-16 21:57:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 21:57:16
//

#include "../includes/extern.h"
#include "../includes/philosophers.h"

static bool	waitForPhilosophers(t_table *table, t_philo *philosophers) {
  int		i;

  i = 0;
  while (i < table->nbPhilos) {
    if (pthread_join(philosophers[i++].thread, NULL) != 0)
      return false;
  }
  return true;
}

static void	*philosopherAlgorithm(void *_philosopher) {
  t_philo	*philosopher;

  philosopher = (t_philo *)_philosopher;
  pthread_barrier_wait(&philosopher->table->barrier);

  while (!philosopher->table->limitReached || philosopher->nbMeals < philosopher->table->mealsLimit)
    {
      if (philosopher->lastAction == UNDEFINED || philosopher->lastAction == SLEEP)
	philoThink(philosopher);

      else if (philosopher->lastAction == UNDEFINED || philosopher->lastAction == THINK)
	philoEat(philosopher);

      else
	philoSleep(philosopher);
    }
  pthread_exit(NULL);
}

/*
** Check Parameters.
*/
static bool	checkParameters(char **argv) {
  if ((atoi(argv[2]) <= 0) ||
      (atoi(argv[4]) <= 0))
    return false;
  if ((strcmp(argv[1], "-p") != 0) ||
      (strcmp(argv[3], "-e") != 0))
    return false;
  return true;
};

static bool	initPhilosopher(t_table *table, char **argv) {
  int		i;

  if (!checkParameters(argv))
    return false;

  table->nbPhilos = atoi(argv[2]);
  table->mealsLimit = atoi(argv[4]);
  table->limitReached = false;
  if (pthread_cond_init(&table->cond, NULL) != 0)
    return false;

  if (table->nbPhilos <= 1)
    return false;
  
  pthread_mutex_t	_bowls[table->nbPhilos];
  t_philo		philosophers[table->nbPhilos];

  table->bowls = _bowls;
  i = 0;
  while (i < table->nbPhilos)
    if (pthread_mutex_init(&table->bowls[i++], NULL) != 0)
      return false;

  if (pthread_barrier_init(&table->barrier, NULL, table->nbPhilos) != 0)
    return false;
  
  i = 0;
  while (i < table->nbPhilos) {
    philosophers[i].id = i;
    philosophers[i].nbMeals = 0;
    philosophers[i].lastAction = UNDEFINED;
    philosophers[i].table = table;
    philosophers[i].timeToEat = 100;
    philosophers[i].timeToSleep = 100;
    philosophers[i].timeToThink = 100;

    if (pthread_create(&philosophers[i].thread, NULL, &philosopherAlgorithm, &philosophers[i]) != 0)
      return false;
    i++;
  }
  if (!waitForPhilosophers(table, philosophers))
    return false;
  return true;
}

static bool     LaunchPhilosopher(char **argv) {
  t_table	table;

  srand(time(NULL));
  if (!initPhilosopher(&table, argv)) {
    RCFCleanup();
    return EXIT_FAILURE;
  }
   RCFCleanup();
  return EXIT_SUCCESS;
}

int		main(int argc, char **argv) 
{
   RCFStartup(argc, argv);
  return argc == 5 ? LaunchPhilosopher(argv) : EXIT_FAILURE;
}
