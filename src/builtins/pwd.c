# include "minishell.h"

int pwd_builtin(t_data *data)
{
    char cwd[1024];
    char *dir;

    dir = getcwd(cwd, sizeof(cwd));
    if (!dir)
    {
        perror("minishell: pwd: ");
        data->exit_status = EXIT_FAILURE;
        return (EXIT_FAILURE);
    }

    printf("%s\n", dir);
    data->exit_status = EXIT_SUCCESS;
	free(dir);
    return (EXIT_SUCCESS);
}