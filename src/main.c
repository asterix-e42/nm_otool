#include "nm_otool.h"

int main(int ac, char **av)
{
	if (ac < 2)
		make_magic("./a.out", 0);
	else
		while(*++av)
			make_magic(*av, ac);
	return (0);
}
