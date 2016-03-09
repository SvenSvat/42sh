/*
** errors.c for 42sh in /home/bauer_a/rendu/PSU_2014_42sh
** 
** Made by Hugo Bauer
** Login   <bauer_a@epitech.net>
** 
** Started on  Wed May 20 17:23:35 2015 Hugo Bauer
** Last update Sun Jun  7 12:58:05 2015 Hugo Bauer
*/

#include <stdio.h>

int		error_cmd_not_found(char *cmd, int exit)
{
  fprintf(stderr, "%s: command not found.\n", cmd);
  return (exit);
}

int		error_syntax_error(int exit)
{
  fprintf(stderr, "Invalid null command.\n");
  return (exit);
}
