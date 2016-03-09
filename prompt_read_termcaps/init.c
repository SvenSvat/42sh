/*
** init.c for prompt in /home/blanqu_a/Workspace/rendu/PSU_2014_42sh/prompt_read_termcaps
** 
** Made by Adrien Blanquer
** Login   <blanqu_a@epitech.net>
** 
** Started on  Mon May 18 15:45:58 2015 Adrien Blanquer
** Last update Sun Jun  7 15:09:06 2015 Adrien Blanquer
*/

#include <stdlib.h>
#include "shell.h"

void		*init_stock()
{
  t_stock	*ptr;

  if ((ptr = malloc(sizeof(t_stock))) == NULL)
    return (NULL);
  if ((ptr->cmd = malloc(sizeof(char) * 4096)) == NULL)
    return (NULL);
  if ((ptr->c = malloc(sizeof(char) * 8)) == NULL)
    return (NULL);
  ptr->pos = 0;
  clean(ptr->cmd, 4096);
  clean(ptr->c, 8);
  return (ptr);
}
