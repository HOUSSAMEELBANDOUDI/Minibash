#include "minishell.h"

void	copy_env(t_list **list, char **env, t_data *data)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			data->home = ft_calloc(1, ft_strlen(&env[i][5]) + 1);
			ft_strlcpy(data->home, &env[i][5], ft_strlen(&env[i][5]) + 1);
		}
	}
}