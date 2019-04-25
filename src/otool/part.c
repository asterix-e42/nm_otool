#include "libft.h"
#include "nm_otool.h"

void print_otool(char *ptr, struct section_64 *section, int offset, int size)
{
	int i;
	int tmp[1];

	i = 0;
	while (i < size)
	{
		if (!(i & 15))
		{
			*tmp = i + section->addr;
			putnb(tmp, "\t");
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

void	nmotool_part(struct section_64 *section, int i, char *ptr)
{
		if (!ft_strcmp(section->segname,  "__TEXT")
				&& !ft_strcmp(section->sectname, "__text"))
		{
			ft_putendl("Contents of (__TEXT,__text) section");//



			print_otool(ptr, section, section->offset, section->size);



		}
		else if (!ft_strcmp(section->segname,  "__BSS")
				&& !ft_strcmp(section->sectname, "__bss"))
			;//
		else if (!ft_strcmp(section->segname,  "__DATA")
				&& !ft_strcmp(section->sectname, "__data"))
			;
}
