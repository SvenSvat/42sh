/*
** loop_read.c for prompt in /home/blanqu_a/Workspace/rendu/PSU_2014_42sh/prompt_read_termcaps
** 
** Made by Adrien Blanquer
** Login   <blanqu_a@epitech.net>
** 
** Started on  Sat May 16 10:50:56 2015 Adrien Blanquer
** Last update Sun Jun  7 15:28:10 2015 Adrien Blanquer
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "lib.h"

void	clean(char *c, const int nb)
{
  int	i;

  i = 0;
  while (i < nb)
    c[i++] = '\0';
}

void	*go_start_line(t_stock *ptr)
{
  print_cursor_left(ptr->pos);
  ptr->pos = 0;
  return (ptr);
}

void	*go_end_line(t_stock *ptr)
{
  print_cursor_right(my_strlen(ptr->cmd) - ptr->pos);
  ptr->pos = my_strlen(ptr->cmd);
  return (ptr);
}

void	*change_word(t_stock *ptr)
{
  int	tmp;

  tmp = ptr->pos;
  if (ptr->c[0] == 27 && ptr->c[1] == 91 && ptr->c[2] == 49 &&
      ptr->c[3] == 59 && ptr->c[4] == 53 && ptr->c[5] == 68)
    {
      if (ptr->cmd[tmp] == ' ' && tmp > 0)
	tmp--;
      while (tmp > 0 && ptr->cmd[tmp] != ' ')
	tmp--;
      print_cursor_left(ptr->pos - tmp);
      ptr->pos = tmp;
    }
  if (ptr->c[0] == 27 && ptr->c[1] == 91 && ptr->c[2] == 49 &&
      ptr->c[3] == 59 && ptr->c[4] == 53 && ptr->c[5] == 67)
    {
      if (ptr->cmd[tmp] == ' ' && tmp < my_strlen(ptr->cmd))
	tmp++;
      while (ptr->cmd[tmp] && ptr->cmd[tmp] != ' ')
	tmp++;
      print_cursor_right(tmp - ptr->pos);
      ptr->pos = tmp;
    }
  return (ptr);
}

char		*loop(t_history *list)
{
  t_stock	*ptr;
  int		i;

  i = 0;
  if ((ptr = init_stock()) == NULL)
    return (NULL);
  while (ptr->c[0] != '\n')
    {
      if (i++ >= 4095)
	return (ptr->cmd);
      clean(ptr->c, 8);
      if (read(0, ptr->c, 7) <= 0)
	break;
      if (ptr->c[1] == '[' && (ptr->c[2] == 'A' || ptr->c[2] == 'B'))
	ptr = gere_history(ptr->cmd, ptr->c, list, ptr);
      if (my_strlen(ptr->c) >= 3)
	  ptr = moves(ptr);
      if (my_strlen(ptr->c) == 1 || my_strlen(ptr->c) == 4)
	if ((ptr = gere_char(ptr)) == NULL)
	  return (NULL);
    }
  return (ptr->cmd);
}
