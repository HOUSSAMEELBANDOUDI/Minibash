#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

void	cd_builtin(t_data *data, char **args)
{
	int			len;
	struct stat	file_info;

	len = ft_arrsize(args);
	if (len > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	else if (len == 1)
	{
		// Change to the home directory
		if (chdir(data->home) != 0)
		{
			perror("cd");
			data->exit_status = 1;
		}
		else
		{
			data->exit_status = 0;
		}
	}
	else if (len == 2)
	{
		if (stat(args[1], &file_info) != 0)
		{
			ft_printf_fd(2, "cd: %s: No such file or directory\n", args[1]);
			data->exit_status = 1;
			return ;
		}
		// Change to the specified directory
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			data->exit_status = 1;
		}
		else
		{
			data->exit_status = 0;
		}
	}
}
