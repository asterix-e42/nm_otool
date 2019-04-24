
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"



int		make_magic(char *filename)
{
	int			magic;
	int			fd;
	struct stat	buf;
	char		*ptr;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		handle_error("file doesn't exist");
		return (-1);
	}
	if (fstat(fd, &buf) < 0)
	{
		handle_error("error file format");
		return(-1);
	}
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		handle_error("cannot allocated");
		return(-1);
	}

	magic = *(int *)ptr;

	if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_64(ptr, buf);//32
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_64(ptr, buf);//gere endian
	else
		handle_error("unknown file format");

	if (munmap(ptr, buf.st_size) < 0)
	{
		handle_error("cannot disallocated");
		return(-1);
	}

	return (1);
}
