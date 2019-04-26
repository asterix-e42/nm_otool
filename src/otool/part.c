#include "libft.h"
#include "nm_otool.h"

void	print_otool_64(char *ptr, struct section_64 *section, int offset,
		int size)
{
	int					i;
	unsigned long long	tmp[1];

	i = 0;
	while (i < size)
	{
		if (!(i & 15))
		{
			*tmp = i + section->addr;
			putnb(tmp, "\t", 0);
		}
		ft_putchar_hex(*(ptr + offset + i));
		ft_putchar(' ');
		i++;
		if (!(i & 15))
			ft_putchar('\n');
	}
	if ((i & 15))
		ft_putchar('\n');
}

void	print_otool_32(char *ptr, struct section *section, int offset, int size)
{
	int					i;
	unsigned long long	tmp[1];

	i = 0;
	while (i < size)
	{
		if (!(i & 15))
		{
			*tmp = (unsigned long long)(i + section->addr);
			putnb(tmp, "\t", 8);
		}
		ft_putchar_hex(*(ptr + offset + i));
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
		ft_putendl("Contents of (__TEXT,__text) section");
		if (!is_64)
			print_otool_64(ptr, section, section->offset, section->size);
		else
			print_otool_32(ptr, (struct section *)section,
					section->offset, section->size);
	}
	else if (!ft_strcmp(section->segname, "__BSS")
			&& !ft_strcmp(section->sectname, "__bss"))
		;
	else if (!ft_strcmp(section->segname, "__DATA")
			&& !ft_strcmp(section->sectname, "__data"))
		;
}
