#include "minishell.h"

int	verify(int result, char *str, char **cmd, char **env)
{
	if (result == 0)
	{
		verify_permission(str, cmd, env);
		return (0);
	}
	return (-1);
}
