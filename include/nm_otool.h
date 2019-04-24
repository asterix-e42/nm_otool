#ifndef NM_OTOOL_H
# define NM_OTOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/nlist.h>
#include <mach-o/loader.h>

void handle_error(char *s);
void    nmotool_part(struct section_64 *section, int i, char *ptr);
char	*get_segment();

#endif
