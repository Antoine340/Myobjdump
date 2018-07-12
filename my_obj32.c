/*
** my_obj32.c for my_objdump in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Sat Feb 18 17:22:29 2017 chauvin
** Last update Sat Feb 18 17:22:31 2017 chauvin
*/

#include <stdio.h>
#include "my_objdump.h"

uint32_t 	get_flags_32(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
  uint32_t	flags;


  flags = 0;
  if (elf->e_type == BFD_NO_FLAGS)
    return (0);
  if (elf->e_type == EXEC_P)
    flags |= EXEC_P;
  if (elf->e_type == ET_DYN)
    flags |= DYNAMIC;
  if (elf->e_type == HAS_RELOC)
    flags |= HAS_RELOC;
  if (shdr->sh_type != SHT_SYMTAB || shdr->sh_type != SHT_DYNAMIC)
    flags |= HAS_SYMS;
  if (elf->e_phnum != 0)
    flags |= D_PAGED;
  return (flags);
}

void	print_flags32_extend(int check, Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
  if (shdr->sh_type != SHT_SYMTAB || shdr->sh_type != SHT_DYNAMIC)
    {
      if (check != 0)
	printf(", ");
      printf("HAS_SYMS");
      check++;
    }
  if (elf->e_type == ET_DYN)
    {
      if (check != 0)
	printf(", ");
      printf("DYNAMIC");
      check++;
    }
  if (elf->e_phnum != 0)
    {
      if (check != 0)
	printf(", ");
      printf("D_PAGED");
    }
}

void	print_flags_32(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
  int	check;

  check = 0;
  if (elf->e_type == BFD_NO_FLAGS)
    printf("NONE");
  if (elf->e_type == EXEC_P)
    {
      printf("EXEC_P");
      check++;
    }
  if (elf->e_type == HAS_RELOC)
    {
      if (check != 0)
	printf(", ");
      printf("HAS_RELOC");
      check++;
    }
  print_flags32_extend(check, elf, shdr);
}

void 	my_obj32(Elf32_Ehdr *elf, char *name)
{
  Elf32_Shdr	*shdr;
  char	*strtab;

  shdr = (Elf32_Shdr *) ((void*)elf + elf->e_shoff);
  strtab = (char*)((void*) elf + shdr[elf->e_shstrndx].sh_offset);
  printf("\n%s:     file format elf32-i386\n", name);
  printf("architecture: i386, flags 0x%08x:\n", get_flags_32(elf, shdr));
  print_flags_32(elf, shdr);
  printf("\nstart address 0x%08x\n\n", (int)elf->e_entry);
  print_32(strtab, elf, shdr);
}