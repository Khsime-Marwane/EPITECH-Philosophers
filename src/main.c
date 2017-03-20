/*
** main.c for main in /home/marwane/Projets/Epitech/C/PSU/PSU_2016_philo/src
** 
** Made by Marwane
** Login   <marwane.khsime@epitech.eu>
** 
** Started on  Sun Mar 19 12:16:40 2017 Marwane
** Last update Sun Mar 19 12:34:39 2017 Marwane
*/

#include "extern.h"
#include "philosophers.h"

static bool	LaunchPhilosopher(char **argv)
{
  t_table	table;

  srand(time(NULL));
  if (!initPhilosopher(&table, argv)) {
    RCFCleanup();
    return (EXIT_FAILURE);
  }
  RCFCleanup();
  return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
  RCFStartup(argc, argv);
  return (argc == 5 ? LaunchPhilosopher(argv) : EXIT_FAILURE);
}
