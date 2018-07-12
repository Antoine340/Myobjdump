/*
** my_objdump.c for my_objdump in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Thu Feb 16 14:50:53 2017 chauvin
** Last update Thu Feb 16 14:50:54 2017 chauvin
*/

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <elf.h>
#include "my_objdump.h"

void	launch_obj(char *name, void *buf, struct stat s)
{
  Elf64_Ehdr *elf;

  elf = buf;
  if (check_elf(elf, name) == -1)
    return ;
  if (elf->e_ident[EI_CLASS] == ELFCLASS32)
    {
      if (check_file_32((Elf32_Ehdr *) elf, s, name) == -1)
	return ;
      my_obj32((Elf32_Ehdr *) elf, name);
    }
  if (elf->e_ident[EI_CLASS] == ELFCLASS64)
    {
      if (check_file_64(elf, s, name) == -1)
	return ;
      my_obj64(elf, name);
    }
}

int	read_obj(char *name)
{
  int fd;
  void *buf;
  struct stat s;

  if ((fd = open(name, O_RDONLY)) == -1)
    {
      fprintf(stderr, "objdump: %s: No such file\n", name);
      return (-1);
    }
  if (fstat(fd, &s) == -1)
    return (perror("fstat"), -1);
  if (s.st_size == 0)
    return (-1);
  if ((buf = mmap(NULL, (size_t) s.st_size, PROT_READ,
		  MAP_PRIVATE, fd, 0)) == (void *) -1)
    {
      close(fd);
      return (perror("mmap"), -1);
    }
  launch_obj(name, buf, s);
  if (close(fd) == -1)
    return (perror("close"), -1);
  if (munmap(buf, (size_t) s.st_size) == -1)
    return (perror("munmap"), -1);
  return (0);
}

int 	main(int ac, char **av)
{
  int	i;

  i = 1;
  if (ac > 1)
    {
      while (i != ac)
	{
	  read_obj(av[i]);
	  i++;
	}
    }
  else
    read_obj("a.out");
  return (0);
}