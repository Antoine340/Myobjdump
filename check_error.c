/*
** check_error.c for objdump in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Sun Feb 26 21:39:10 2017 chauvin
** Last update Sun Feb 26 21:39:20 2017 chauvin
*/

#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include "my_objdump.h"

int	check_elf(Elf64_Ehdr *elf, char *file)
{
  if ((elf->e_type != ET_EXEC
       && elf->e_type != ET_REL
       && elf->e_type != ET_DYN)
      || elf->e_ident[EI_MAG0] != ELFMAG0
      || elf->e_ident[EI_MAG1] != ELFMAG1
      || elf->e_ident[EI_MAG2] != ELFMAG2
      || elf->e_ident[EI_MAG3] != ELFMAG3)
    {
      fprintf(stderr, "objdump: %s: File format not recognized\n", file);
      return (-1);
    }
  return (0);
}

int	check_file_64(Elf64_Ehdr *elf, struct stat s, char *name)
{
  Elf64_Shdr	*section_header;
  char 		*strtab;
  int 		i;

  i = 0;
  section_header = (Elf64_Shdr *) ((void *)elf + elf->e_shoff);
  strtab = (char *) ((void *) elf + section_header[elf->e_shstrndx].sh_offset);
  while (i != elf->e_shnum)
    {
      if (&strtab[section_header[i].sh_name] > (char *) (elf + s.st_size))
	{
	  fprintf(stderr, "objdump: %s: File truncated\n", name);
	  return (-1);
	}
      if (section_header[i].sh_offset
	  + section_header[i].sh_size > (unsigned  int) s.st_size)
	{
	  fprintf(stderr, "objdump: %s: File format not recognized\n", name);
	  return (-1);
	}
      i++;
    }
  return (0);
}

int	check_file_32(Elf32_Ehdr *elf, struct stat s, char *name)
{
  Elf32_Shdr	*section_header;
  char 		*strtab;
  int 		i;

  i = 0;
  section_header = (Elf32_Shdr *) ((void *)elf + elf->e_shoff);
  strtab = (char *) ((void *) elf + section_header[elf->e_shstrndx].sh_offset);
  while (i != elf->e_shnum)
    {
      if (&strtab[section_header[i].sh_name] > (char *) (elf + s.st_size))
	{
	  fprintf(stderr, "objdump: %s: File truncated\n", name);
	  return (-1);
	}
      if (section_header[i].sh_offset
	  + section_header[i].sh_size > (unsigned  int) s.st_size)
	{
	  fprintf(stderr, "objdump: %s: File format not recognized\n", name);
	  return (-1);
	}
      i++;
    }
  return (0);
}