#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"
#include <ar.h>
#include <mach-o/ranlib.h>

void magic(void *ptr, struct stat buf, char *d, int pute);

void archive(void *ptr, struct stat buf, char *av)
{
	struct ar_hdr *archive;
	int jmp_1;
	int i;
	char *aff;

	i = 0;
	archive = ptr + SARMAG;
	while(*(char *)archive)
	{
		jmp_1 = ft_atoi(archive->ar_name + 3);
		//ft_putnbr(jmp_1);
		if (ft_strncmp((char *)(archive + 1), SYMDEF, 9))
		{
		aff = malloc(jmp_1 + ft_strlen(av) + 3);
		ft_strcpy(aff, av);
		ft_strcpy(aff + ft_strlen(av), "(");
		ft_strcpy(aff + ft_strlen(av) + 1, (char *)(archive + 1));
		*(aff + ft_strlen(av) + ft_strlen((char *)(archive + 1)) + 1) = ')';
		*(aff + ft_strlen(av) + ft_strlen((char *)(archive + 1)) + 2) = '\0';
		magic(((char *)(archive + 1) + jmp_1), buf, aff, 3);
		free(aff);
		}
		archive = (void *)archive + ft_atoi(archive->ar_size) + sizeof(struct ar_hdr);
		i++;
	}
}

void magic(void *ptr, struct stat buf, char *av, int pute)
{
	int			magic;

	magic = *(int *)ptr;

	if (!ft_strncmp(ARMAG, ptr, 8))
		archive(ptr, buf, av);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_64(ptr, buf, av, pute);//32
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_64(ptr, buf, av, pute);//gere endian
	else
		handle_error("unknown file format");
	get_number_segment(-1);
}

int		make_magic(char *filename, int pute)
{
	int			fd;
	struct stat	buf;
	char		*ptr;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putendl(filename);
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
	magic(ptr, buf, filename, pute);

	if (munmap(ptr, buf.st_size) < 0)
	{
		handle_error("cannot disallocated");
		return(-1);
	}

	return (1);
}
