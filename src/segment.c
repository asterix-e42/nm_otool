#include "libft.h"
#include "nm_otool.h"


void putnb(int *number, char *str)
{
	char *ret;
	char *ret_2;

	ret = ft_itoabase(*(number + 1) , "0123456789abcdef");
	ret_2 = ft_itoabase(*number, "0123456789abcdef");
	if (ft_strlen(ret) == 1 && *ret == '0')
		write(1, "0000000000000000", 15 - ft_strlen(ret_2));
	else
		write(1, "0000000000000000", 8 - ft_strlen(ret));
	ft_putstr(ret);
	ft_putstr(ret_2);
	ft_putstr(str);
	free(ret);
	free(ret_2);
}

void set_segment(struct segment_command_64  *segment, void *ptr)
{
	struct section_64 *section;
	struct section_64 *section_tmp;
	int i;
	int j;

	section = segment + 1;
	i = 0;

	while (i < segment->nsects)
	{
		j = 0;
		section_tmp = segment + 1;
		while (j < i)
		{
			if (((section_tmp->addr < section->addr)
						&& ((section_tmp->addr + section_tmp->size) > section->addr))
					|| ((section->addr < section_tmp->addr)
						&& ((section->addr + section->size) > section_tmp->addr)))
				handle_error("(section contents at offset");

			section_tmp++;
			j++;
		}



	
		nmotool_part(section, i, ptr);//one or one
	
		




		section++;
		++i;
	}
}
