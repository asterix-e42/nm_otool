/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:16:16 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/13 15:21:12 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "nm_otool.h"
#include <ar.h>
#include <mach-o/ranlib.h>

static inline int	it_is_fat_magic(uint32_t magic, size_t target)
{
	return ((magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	|| (!target && (magic == MH_CIGAM || magic == MH_MAGIC)));
}

int					fat_32(void *ptr, struct stat buf, char *av)
{
	struct fat_arch		*arch;
	struct mach_header	*mptr;
	uint32_t			inc;
	size_t				target_offset;

	inc = -1;
	target_offset = 0;
	arch = ptr + sizeof(struct fat_header);
	while (++inc < endian4(((struct fat_header *)ptr)->nfat_arch))
	{
		if (god(mptr = ptr + endian4(arch->offset), 0))
			return (handle_error("truncated or malformed fat32 file"));
		if ((mptr->cputype % 0x100) != CPU_TYPE_I386 && ++arch)
			continue ;
		if (endian4(arch->offset) == 0)
			return (handle_error("error offset"));
		if (it_is_fat_magic(mptr->magic, target_offset))
			target_offset = endian4(arch->offset);
		if (it_is_fat_magic(mptr->magic, target_offset) && (mptr->filetype - 6))
			break ;
		arch++;
	}
	if (!target_offset)
		return (handle_error("no arch know"));
	return (magic(ptr + target_offset, buf, av, 1));
}

int					fat_64(void *ptr, struct stat buf, char *av)
{
	struct fat_arch_64	*arch;
	struct mach_header	*mptr;
	uint32_t			inc;
	size_t				target_offset;

	inc = -1;
	target_offset = 0;
	arch = ptr + sizeof(struct fat_header);
	while (++inc < endian4(((struct fat_header *)ptr)->nfat_arch))
	{
		if (god(mptr = ptr + endian8(arch->offset), 0))
			return (handle_error("truncated or malformed fat64 file"));
		if ((mptr->cputype % 0x100) != CPU_TYPE_I386 && ++arch)
			continue ;
		if (endian8(arch->offset) == 0)
			return (handle_error("error offset"));
		if (it_is_fat_magic(mptr->magic, target_offset))
			target_offset = endian8(arch->offset);
		if (it_is_fat_magic(mptr->magic, target_offset) && (mptr->filetype - 6))
			break ;
		arch++;
	}
	if (magic(ptr + target_offset, buf, av, 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int					magic(void *ptr, struct stat buf, char *av, int pute)
{
	uint32_t				*magic;
	int32_t					ret;

	magic = (uint32_t *)ptr;
	endian_mode(*magic);
	is_arch((*(magic + 3)) == 1);
	if (!ft_strncmp(ARMAG, ptr, 8))
		ret = archive(ptr, buf, av);
	else if (*magic == FAT_MAGIC_64 || *magic == FAT_CIGAM_64)
		ret = fat_64(ptr, buf, av);
	else if (*magic == FAT_MAGIC || *magic == FAT_CIGAM)
		ret = fat_32(ptr, buf, av);
	else if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		ret = handle_32(ptr, buf, av, pute);
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		ret = handle_64(ptr, buf, av, pute);
	else
		ret = handle_error(("unknown file format"));
	is_arch((*(magic + 3)) == 1);
	get_number_segment(-1);
	return (ret);
}

int					make_magic(char *filename, int pute)
{
	int			fd;
	struct stat	buf;
	char		*ptr;
	int			ret;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (handle_error("file doesn't exist"));
	if (fstat(fd, &buf) < 0)
		return (handle_error("error file format"));
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (handle_error("cannot allocated"));
	if (*(ptr + buf.st_size - 1) != '\0' && *(ptr + buf.st_size - 1) != '\x0a')
		return (handle_error("binary non valide"));
	god(ptr + buf.st_size, 1);
	ret = magic(ptr, buf, filename, pute);
	god(NULL, 1);
	if (munmap(ptr, buf.st_size) < 0)
		return (handle_error("cannot disallocated"));
	if (get_segment(1) == NULL)
		return (ret);
	return (EXIT_FAILURE);
}
