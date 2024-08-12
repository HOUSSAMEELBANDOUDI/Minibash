#include "minishell.h"

static char *get_env_var_value(t_list *env, const char *var)
{
    t_list *current;
    char *tmp;
    char *value;
    int len;

    if (!env || !var)
        return (NULL);
    len = ft_strlen(var);
    tmp = ft_strjoin(var, "=");
    if (!tmp)
        return (NULL);
    current = env;
    while (current)
    {
        if (current->content)
        {
            if (ft_strncmp(tmp, (char *)current->content, len + 1) == 0)
            {
                free(tmp);
                value = ft_strchr((char *)current->content, '=');
                if (value)
                    return (value + 1); // Return the value part of the environment variable
            }
        }
        current = current->next;
    }
    free(tmp);
    return (NULL);
}


void cd_builtin(t_data *data, char **args)
{
    int         len;
    struct stat file_info;
    char        *path;

    len = ft_arrsize(args);

    if (len > 2)
    {
        ft_putendl_fd("cd: too many arguments", 2);
        data->exit_status = 1;
        return ;
    }
    
    if (len == 1)
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
        if (ft_strncmp(args[1], "-", 2) == 0)
        {
            // Handle "cd -" case
            path = get_env_var_value(data->env, "OLDPWD");
            if (path == NULL)
            {
                ft_putendl_fd("cd: OLDPWD not set", 2);
                data->exit_status = 1;
                return ;
            }
            if (chdir(path) != 0)
            {
                perror("cd");
                data->exit_status = 1;
                return ;
            }
            // Print the path we are changing to
            printf("%s\n", path);
            data->exit_status = 0;
        }
        else
        {
            // Handle "cd <directory>" case
            if (stat(args[1], &file_info) != 0)
            {
                ft_printf_fd(2, "cd: %s: No such file or directory\n", args[1]);
                data->exit_status = 1;
                return ;
            }
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
}
