#include "libft.h"
#include "nm_otool.h"

char	*get_segment()
{
	static char *section_letter = NULL;
	if (!section_letter)
	{
		section_letter = malloc(sizeof(char) * MAX_SECT);
		section_letter = ft_memset(section_letter, 0, MAX_SECT);
	}
	return (section_letter);
}

void	nmotool_part(struct section_64 *section, int i, char *ptr)
{
	char *section_leter;

	(void)ptr;
	section_leter = get_segment();
		if (!ft_strcmp(section->segname,  "__TEXT")
				&& !ft_strcmp(section->sectname, "__text"))
		{
			section_leter[i] = 'T';
		}
		else if (!ft_strcmp(section->segname,  "__BSS")
				&& !ft_strcmp(section->sectname, "__bss"))
			section_leter[i] = 'B';
		else if (!ft_strcmp(section->segname,  "__DATA")
				&& !ft_strcmp(section->sectname, "__data"))
			section_leter[i] = 'D';
}
