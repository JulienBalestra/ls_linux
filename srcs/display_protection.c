#include "ls.h"

static char	get_type(mode_t mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else
		return ('p');
}

int	is_symbolic_link(t_item *link)
{
	return (S_ISLNK(link->stats->st_mode) ? 1 : 0);
}

int	is_directory(t_item *link)
{
	return (S_ISDIR(link->stats->st_mode) ? 1 : 0);
}

void	display_protection(mode_t st_mode, char *path)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		not_enough_memory(NULL);
	str[0] = get_type(st_mode);
	str[1] = ((st_mode & S_IRUSR) ? 'r' : '-');
	str[2] = ((st_mode & S_IWUSR) ? 'w' : '-');
	str[3] = ((st_mode & S_IXUSR) ? 'x' : '-');
	if (st_mode & S_ISUID)
		str[3] = ((st_mode & S_IXUSR) ? 's' : 'S');
	str[4] = ((st_mode & S_IRGRP) ? 'r' : '-');
	str[5] = ((st_mode & S_IWGRP) ? 'w' : '-');
	str[6] = ((st_mode & S_IXGRP) ? 'x' : '-');
	if (st_mode & S_ISGID)
		str[6] = ((st_mode & S_IXGRP) ? 's' : 'S');
	str[7] = ((st_mode & S_IROTH) ? 'r' : '-');
	str[8] = ((st_mode & S_IWOTH) ? 'w' : '-');
	str[9] = ((st_mode & S_IXOTH) ? 'x' : '-');
	if (st_mode & S_ISVTX)
		str[9] = ((st_mode & S_IXUSR) ? 't' : 'T');
	(void)path;
	//str[10] = (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 1) ? '@' : ' ';
	str[10] = ' ';
	str[11] = '\0';
	ft_putstr(str);
	free(str);
}