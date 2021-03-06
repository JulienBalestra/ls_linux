#include "ls.h"

DIR	*open_dir(char *file_name)
{
	if (file_name)
		return (opendir(file_name));	
	else
		return (NULL);
}

static void			do_readdir(DIR *fd_file, t_item *parent, t_args *args)
{
	struct dirent	*sub_dir;
	t_item			*link;
	
	link = NULL;	
	sub_dir = NULL;
	while ((sub_dir = readdir(fd_file)))
	{
		if (args->options->a == 0 && sub_dir->d_name[0] == '.')
			;
		else
		{
			link = new_link(sub_dir->d_name, parent, args);
			if (parent->child)
				add_link(&(parent)->child, link, args->options->U);
			else
				parent->child = link;
		}
	}
}

void			create_children(t_item *parent, t_args *args)
{
	DIR		*fd_file;

	fd_file = NULL;
	if (parent && parent->path)
	{
		if (args->options->d == 1 && parent != NULL)
			return ;
		if ((fd_file = open_dir(parent->path)))
		{
			do_readdir(fd_file, parent, args);
			parent->child = merge_sort_list_recursive(parent->child, args);
			deep_in_directories(parent->child, args);
		}
	}
	fd_file ? closedir(fd_file) : 1;
}