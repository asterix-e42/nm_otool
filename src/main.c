
int main(int ac, char **av)
{
	if (ac != 2)
	{
		make_magic("./a.out");
	}
	else
	{
		make_magic(av[1]);
	}
	return (0);
}
