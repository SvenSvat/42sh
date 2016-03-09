/*
** move.c for prompt in /home/blanqu_a/Workspace/rendu/PSU_2014_42sh/prompt_read_termcaps
** 
** Made by Adrien Blanquer
** Login   <blanqu_a@epitech.net>
** 
** Started on  Sat May 16 16:04:26 2015 Adrien Blanquer
** Last update Sun Jun  7 15:25:28 2015 Adrien Blanquer
*/

#include "shell.h"
#include "lib.h"

char	*up(char *cmd, t_history **tmp, int *cpt, char **c)
{
  clean(*c, 8);
  clean_line();
  my_putchar('\r', 1);
  pars_ps1(g_data->env);
  my_putstr((*tmp)->data, 1);
  my_strcpy(cmd, (*tmp)->data);
  if ((*tmp)->next)
    (*tmp) = (*tmp)->next;
  *cpt = my_strlen(cmd);
  return (cmd);
}

char	*down(char *cmd, t_history **tmp, int *cpt, char **c)
{
  clean(*c, 8);
  if ((*tmp)->prev)
    {
      clean_line();
      my_putchar('\r', 1);
      pars_ps1(g_data->env);
      *tmp = (*tmp)->prev;
      my_putstr((*tmp)->data, 1);
      my_strcpy(cmd, (*tmp)->data);
      *cpt = my_strlen(cmd);
    }
  else
    {
      clean(cmd, 4096);
      *cpt = 0;
      clean_line();
      my_putchar('\r', 1);
      pars_ps1(g_data->env);
    }
  return (cmd);
}

void	*moves(t_stock *ptr)
{
  if (ptr->c[1] == '[' && (ptr->c[2] == 'C' || ptr->c[2] == 'D'))
    ptr = gere_arrow(ptr);
  if (ptr->c[0] == 27 && ptr->c[1] == 79 && ptr->c[2] == 72)
    ptr = go_start_line(ptr);
  if (ptr->c[0] == 27 && ptr->c[1] == 79 && ptr->c[2] == 70)
    ptr = go_end_line(ptr);
  if (my_strlen(ptr->c) == 6)
    ptr = change_word(ptr);
  return (ptr);
}
