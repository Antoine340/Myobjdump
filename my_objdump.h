/*
** my_objdump.h for my_objdump.h in /home/chauvin/Rendu-2017-Epitech/Sys_Unix/PSU_2016_nmobjdump
** 
** Made by chauvin
** Login   <chauvi_d>
** 
** Started on  Thu Feb 16 15:17:19 2017 chauvin
** Last update Thu Feb 16 15:18:12 2017 chauvin
*/

#include <elf.h>
#include <sys/stat.h>
#include "flags.h"

#ifndef MY_OBJDUMP_H_
# define MY_OBJDUMP_H_

void 	my_obj32(Elf32_Ehdr *elf, char *name);
void 	my_obj64(Elf64_Ehdr *elf, char *name);
void	print_64(char	*strtab, Elf64_Ehdr *elf, Elf64_Shdr *shdr);
void	print_32(char	*strtab, Elf32_Ehdr *elf, Elf32_Shdr *section_header);
void	my_printf_adr(unsigned int adr, unsigned int max);
int	check_elf(Elf64_Ehdr *elf, char *file);
int	check_file_64(Elf64_Ehdr *elf, struct stat s, char *name);
int	check_file_32(Elf32_Ehdr *elf, struct stat s, char *name);

#endif /* MY_OBJDUMP_H_ */
