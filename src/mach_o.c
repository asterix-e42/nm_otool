/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 22:16:16 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/03 14:47:26 by tdumouli         ###   ########.fr       */
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

int		archive(void *ptr, struct stat buf, char *av)
{
	struct ar_hdr	*archive;
	int				jmp;
	int				i;
	char			*aff;

	aff = NULL;
	i = -1;
	archive = ptr + SARMAG;
	while (*(char *)archive && (++i >= 0))
	{
		jmp = ft_atoi(archive->ar_name + 3);
		if (ft_strncmp((char *)(archive + 1), SYMDEF, 9))
		{
			if (!(aff = archive_2(jmp, av, (void *)archive)))
				return (EXIT_FAILURE);
			if (magic(((char *)(archive + 1) + jmp), buf, aff, 3))
				return (handle_error_free(aff));
			free(aff);
		}
		if ((void *)(archive = (void *)archive + ft_atoi(archive->ar_size)
			+ sizeof(struct ar_hdr)) - ptr > buf.st_size)
			return (handle_error("error size no correct"));
	}
	return (EXIT_SUCCESS);
}

int		fat_32(void *ptr, struct stat buf, char *av)
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
		if (endian4(arch->offset) == 0)
			return (handle_error("error offset"));
		magic_ptr = (void *)ptr + endian4(arch->offset);
		if (((*(magic_ptr) == MH_MAGIC_64 || *magic_ptr == MH_CIGAM_64) &&
		(temp = 1)) || !temp)
			if (magic(magic_ptr, buf, av, 1))
				return (EXIT_FAILURE);
		arch++;
		endian_mode(*(uint32_t *)ptr == FAT_CIGAM || *(uint32_t *)ptr ==
		FAT_CIGAM_64 || *(uint32_t *)ptr == MH_CIGAM ||
		*(uint32_t *)ptr == MH_CIGAM_64);
	}
	return (EXIT_SUCCESS);
}

int		fat_64(void *ptr, struct stat buf, char *av)
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
		if (endian8(arch->offset) == 0)
			return (handle_error("error offset"));
		magic_ptr = (void *)ptr + endian8(arch->offset);
		if (((*(magic_ptr) == MH_MAGIC_64 || *magic_ptr == MH_CIGAM_64)
		&& (temp = 1)) || !temp)
			if (magic(magic_ptr, buf, av, 1))
				return (EXIT_FAILURE);
		arch++;
		endian_mode(*(uint32_t *)ptr == FAT_CIGAM || *(uint32_t *)ptr
		== FAT_CIGAM_64 || *(uint32_t *)ptr == MH_CIGAM
		|| *(uint32_t *)ptr == MH_CIGAM_64);
	}
	return (EXIT_SUCCESS);
}

int		magic(void *ptr, struct stat buf, char *av, int pute)
{
	unsigned int			magic;
	int						ret;

	magic = *(int *)ptr;
	endian_mode(magic == FAT_CIGAM || magic == FAT_CIGAM_64 || \
			magic == MH_CIGAM || magic == MH_CIGAM_64);
	if (!ft_strncmp(ARMAG, ptr, 8))
		ret = archive(ptr, buf, av);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		ret = fat_64(ptr, buf, av);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		ret = fat_32(ptr, buf, av);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		ret = handle_32(ptr, buf, av, pute);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		ret = handle_64(ptr, buf, av, pute);
	else
		ret = handle_error(("unknown file format"));
	get_number_segment(-1);
	return (ret);
}

int		make_magic(char *filename, int pute)
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
