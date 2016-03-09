/*
** gnl.c for gnl in /home/geiger_a/rendu/gnl
** 
** Made by anthony geiger
** Login   <geiger_a@epitech.net>
** 
** Started on  Wed May  6 14:59:58 2015 anthony geiger
** Last update Sun Jun  7 13:06:59 2015 anthony geiger
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

char            *my_spstrconcat(char *s1, char *s2)
{
  char          *ret;
  int           i;
  int           j;

  i = 0;
  j = 0;
  if ((ret = malloc(sizeof(char) * (strlen(s1)
				    + strlen(s2)) + 1)) == NULL)
    return (NULL);
  while (s1[i])
    {
      ret[j] = s1[i];
      ++j;
      ++i;
    }
  i = 0;
  while (s2[i])
    {
      ret[j] = s2[i];
      ++j;
      ++i;
    }
  ret[j] = '\0';
  free(s1);
  return (ret);
}

char		*get_new_line(char **all)
{
  char		*line;
  static int	i;
  int		start;

  start = i;
  if (*all == NULL)
    return (NULL);
  while ((*all)[i] != '\n')
    {
      if ((*all)[i] == '\0')
	{
	  if ((line = strndup((*all) + start, i - start)) == NULL)
	    return (NULL);
	  *all = NULL;
	  i = 0;
	  return (line);
	}
      ++i;
    }
  if ((line = strndup((*all) + start, i - start)) == NULL)
    return (NULL);
  i++;
  return (line);
}

char	*get_str(int fd, char buff[], char **all)
{
  int		ret;

  while ((ret = read(fd, buff, READ_SIZE + 1)) > 0)
    {
      buff[ret] = '\0';
      if (*all == NULL)
	{
	  if ((*all = strdup(buff)) == NULL)
	    return (NULL);
	}
      else
	if ((*all = my_spstrconcat(*all, buff)) == NULL)
	  return (NULL);
    }
  return (*all);
}

char		*gnl(const int fd)
{
  static char	*all = NULL;
  char		buff[READ_SIZE + 1];
  static int	pass;
  char		*line;

  if (pass == 1 && all == NULL)
    {
      pass = 0;
      return (NULL);
    }
  if (pass == 0)
    {
      if (get_str(fd, buff, &all) == NULL)
	return (NULL);
      pass = 1;
    }
  if ((line = get_new_line(&all)) == NULL)
    return (NULL);
  return (line);
}
