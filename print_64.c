/*
** print_64.c for my_objdump in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Mon Feb 20 19:00:50 2017 chauvin
** Last update Mon Feb 20 19:00:51 2017 chauvin
*/

#include <elf.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "my_objdump.h"

void		my_printf_adr(unsigned int adr, unsigned int max)
{
  unsigned int    i;
  int    j;

  i = 1;
  j = 0;
  while (((i < max) && (i *= 16)) || (j < 4))
    j += 1;
  printf(" %0*x ", j, adr);
}

void	print_hexa_64(unsigned int j, unsigned int prev, unsigned char *content)
{
  int	i;

  i = j;
  while (i % 16 != 0)
    {
      if (i % 4 == 0 && i % 16 != 0)
	printf(" ");
      printf("  ");
      i++;
    }
  printf("  ");
  while (prev != j)
    {
      if (isprint(content[prev]))
	printf("%c", content[prev]);
      else
	printf(".");
      prev++;
    }
  while (prev % 16 != 0)
    {
      printf(" ");
      prev++;
    }
  printf("\n");
}

void		print_section64(char *strtab, Elf64_Ehdr *elf, Elf64_Shdr *shdr, int i)
{
  unsigned int		j;
  unsigned int		prev;
  size_t		adr;
  unsigned char		*content;

  j = prev = 0;
  adr = shdr[i].sh_addr;
  content = (unsigned char*)((void *) elf + shdr[i].sh_offset);
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  while (j < shdr[i].sh_size)
    {
      if (j % 16 == 0)
	{
	  my_printf_adr((unsigned int) adr,
			(unsigned int) (shdr[i].sh_addr + shdr[i].sh_size));
	  adr = adr + 16;
	}
      printf("%02x", content[j++]);
      if (j % 16 != 0 && j % 4 == 0 && j < shdr[i].sh_size)
	printf(" ");
      if (j % 16 == 0 || j >= shdr[i].sh_size)
	{
	  print_hexa_64(j, prev, content);
	  prev = j;
	}
    }
}

void	print_64(char	*strtab, Elf64_Ehdr *elf, Elf64_Shdr *section_header)
{
  int	i;

  i = 0;
  while (i != elf->e_shnum)
    {
      if (section_header[i].sh_size != 0
	  && section_header[i].sh_type != SHT_NOBITS
	  && section_header[i].sh_type != SHT_NULL
	  && section_header[i].sh_type != SHT_SYMTAB
	  && (section_header[i].sh_type != SHT_STRTAB
	      || section_header[i].sh_flags == SHF_ALLOC))
	  {
	  if (strcmp(&strtab[section_header[i].sh_name], ".rela.text") != 0
	      && strcmp(&strtab[section_header[i].sh_name], ".rela.eh_frame") != 0
	      && strcmp(&strtab[section_header[i].sh_name], ".rel.text") != 0
	      && strcmp(&strtab[section_header[i].sh_name], ".rel.eh_frame") != 0)
	    print_section64(strtab, elf, section_header, i);
	  }
	  i++;
    }
}