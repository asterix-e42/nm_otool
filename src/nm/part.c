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

void	nmotool_part(struct section_64 *section, int i, char *ptr, char _64)
{
	char *section_leter;

	(void)ptr;
	(void)_64;
	section_leter = get_segment();
		if (!ft_strcmp(section->segname, SEG_TEXT)
				&& !ft_strcmp(section->sectname, SECT_TEXT))
			section_leter[i] = 'T';
		else if (!ft_strcmp(section->segname,  "__BSS")
				&& !ft_strcmp(section->sectname, SECT_BSS))
			section_leter[i] = 'B';
		else if (!ft_strcmp(section->segname,  SEG_DATA)
				&& !ft_strcmp(section->sectname, SECT_DATA))
			section_leter[i] = 'D';
}
