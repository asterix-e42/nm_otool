#include "libft.h"
#include "nm_otool.h"

void	print_content(struct section_64 *s)
{
	ft_putstr("Contents of (");
	ft_putstr(s->segname);
	ft_putstr(",");
	ft_putstr(s->sectname);
	ft_putendl(") section");
}

void	print_otool_64(char *ptr, struct section_64 *section)
{
	uint64_t	i;
	uint64_t	tmp[1];

	i = 0;
	while (i < endian8(section->size))
	{
		if (!(i & 15))
		{
			*tmp = i + endian8(section->addr);
			putnb(tmp, "\t", 0);
		}
		ft_putchar_hex(*(ptr + endian4(section->offset) + i));
		ft_putchar(' ');
		i++;
		if (!(i & 15))
			ft_putchar('\n');
	}
	if ((i & 15))
		ft_putchar('\n');
}

void	print_otool_32(char *ptr, struct section *section)
{
	uint32_t	i;
	uint64_t	tmp[1];

	i = 0;
	while (i < endian4(section->size))
	{
		if (!(i & 15))
		{
			*tmp = (uint64_t)(i + endian4(section->addr));
			putnb(tmp, "\t", 8);
		}
		ft_putchar_hex(*(ptr + endian4(section->offset) + i));
		ft_putchar(' ');
		i++;
		if (!(i & 15))
			ft_putchar('\n');
	}
	if ((i & 15))
		ft_putchar('\n');
}

void	nmotool_part(struct section_64 *section, int i, char *ptr, char is_64)
{
	(void)i;
	if (!ft_strcmp(section->segname, "__TEXT")
			&& !ft_strcmp(section->sectname, "__text"))
	{
		print_content(section);
		if (!is_64)
			print_otool_64(ptr, section);
		else
			print_otool_32(ptr, (struct section *)section);
	}
	else if (!ft_strcmp(section->segname, "__BSS")
			&& !ft_strcmp(section->sectname, "__bss"))
		;
	else if (!ft_strcmp(section->segname, "__DATA")
			&& !ft_strcmp(section->sectname, "__data"))
		;
}
