#ifndef NM_OTOOL_H
# define NM_OTOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/nlist.h>
#include <mach-o/loader.h>

void	handle_error(char *s);
void    nmotool_part(struct section_64 *section, int i, char *ptr);
char	*get_segment();
void	putnb(int *number, char *str);
void	set_segment(struct segment_command_64  *segment, void *ptr);
int		make_magic(char *filename);
void	print_output_sort(int n, int s, int stroff, char *ptr, struct stat buf);

#endif
