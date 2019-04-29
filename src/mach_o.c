#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"
#include <ar.h>
#include <mach-o/ranlib.h>

void	archive(void *ptr, struct stat buf, char *av)
{
	struct ar_hdr	*archive;
	int				jmp;
	int				i;
	char			*aff;

	i = 0;
	archive = ptr + SARMAG;
	while (*(char *)archive)
	{
		jmp = ft_atoi(archive->ar_name + 3);
		if (ft_strncmp((char *)(archive + 1), SYMDEF, 9))
		{
			aff = malloc(jmp + ft_strlen(av) + 3);
			ft_strcpy(aff, av);
			ft_strcpy(aff + ft_strlen(av), "(");
			ft_strcpy(aff + ft_strlen(av) + 1, (char *)(archive + 1));
			*(aff + ft_strlen(av) + ft_strlen((char *)(archive + 1)) + 1) = ')';
			*(aff + ft_strlen(av) + ft_strlen((char *)(archive + 1)) + 2) = 0;
			magic(((char *)(archive + 1) + jmp), buf, aff, 3);
			free(aff);
		}
		archive = (void *)archive + ft_atoi(archive->ar_size)
			+ sizeof(struct ar_hdr);
		i++;
	}
}

void	fat_32(void *ptr, struct stat buf, char *av)
{
	struct fat_arch		*arch;
	uint32_t			*magic_ptr;
	uint32_t			inc;
	size_t				target_offset;
	char				temp;

	inc = -1;
	temp = 0;
	target_offset = 0;
	arch = ptr + sizeof(struct fat_header);
	while (++inc < endian4(((struct fat_header *)ptr)->nfat_arch))
	{
		magic_ptr = (void *)ptr + endian4(arch->offset);
		if ((*(magic_ptr) == MH_MAGIC_64 || *magic_ptr == MH_CIGAM_64)
		&& (temp = 1))
			magic(magic_ptr, buf, av, 1);
		else if (!temp)
			magic(magic_ptr, buf, av, 1);
		arch++;
		endian_mode(*(uint32_t *)ptr == FAT_CIGAM || *(uint32_t *)ptr
		== FAT_CIGAM_64 || *(uint32_t *)ptr == MH_CIGAM
		|| *(uint32_t *)ptr == MH_CIGAM_64);
	}
}

void	fat_64(void *ptr, struct stat buf, char *av)
{
	struct fat_arch_64	*arch;
	uint64_t			*magic_ptr;
	uint32_t			inc;
	size_t				target_offset;
	char				temp;

	inc = -1;
	temp = 0;
	target_offset = 0;
	arch = ptr + sizeof(struct fat_header);
	while (++inc < endian4(((struct fat_header *)ptr)->nfat_arch))
	{
		magic_ptr = (void *)ptr + endian8(arch->offset);
		if ((*(magic_ptr) == MH_MAGIC_64 || *magic_ptr == MH_CIGAM_64)
		&& (temp = 1))
			magic(magic_ptr, buf, av, 1);
		else if (!temp)
			magic(magic_ptr, buf, av, 1);
		arch++;
		endian_mode(*(uint32_t *)ptr == FAT_CIGAM || *(uint32_t *)ptr
		== FAT_CIGAM_64 || *(uint32_t *)ptr == MH_CIGAM
		|| *(uint32_t *)ptr == MH_CIGAM_64);
	}
}

void	magic(void *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			magic;

	magic = *(int *)ptr;
	endian_mode(magic == FAT_CIGAM || magic == FAT_CIGAM_64 || \
			magic == MH_CIGAM || magic == MH_CIGAM_64);
	if (!ft_strncmp(ARMAG, ptr, 8))
		archive(ptr, buf, av);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		fat_64(ptr, buf, av);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		fat_32(ptr, buf, av);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_32(ptr, buf, av, pute);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_64(ptr, buf, av, pute);
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
		handle_error("file doesn't exist");
	if (fstat(fd, &buf) < 0)
		handle_error("error file format");
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		handle_error("cannot allocated");
	magic(ptr, buf, filename, pute);
	if (munmap(ptr, buf.st_size) < 0)
		handle_error("cannot disallocated");
	return (1);
}
