#include "libft.h"
#include "nm_otool.h"

char		get_symbol_letter(struct nlist_64 array)
{
	char		letter;

	if ((array.n_type & N_TYPE) == N_UNDF)
		letter = (array.n_value) ? 'C' : 'U';
	else if ((array.n_type & N_TYPE) == N_INDR)
		letter = 'I';
	else if ((array.n_type & N_TYPE) == N_ABS)
		letter = 'A';
	else if ((array.n_type & N_STAB))
		letter = '-';
	else if ((array.n_type & N_TYPE) == N_SECT)
	{
		letter = *(get_segment() + array.n_sect - 1);
		letter = (!letter)? 'S' : letter;
	}
	else
		letter = '?';

	if (!(array.n_type & N_EXT) && letter != '?' && letter != '-')
		letter += 32;
	return (letter);
}
