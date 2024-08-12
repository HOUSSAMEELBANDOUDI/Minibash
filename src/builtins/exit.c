#include "minishell.h"

static bool is_quiet_mode(t_data *data)
{
    return (data->process_count > 1); // Adjust based on actual data
}

void exit_builtin(t_data *data, pid_t *pids, char **args)
{
    long num;
    int exit_code;
    bool quiet_mode;

    // Determine if the command should be in quiet mode
    quiet_mode = is_quiet_mode(data);

    // Print "exit" only if the shell is interactive and not in quiet mode
    if (!quiet_mode)
    {
        ft_putendl_fd("exit", 2);
    }

    num = data->exit_status;  // Default to the last exit status
    exit_code = 0;

    // Check for too many arguments
    if (ft_arrsize(args) > 2)
    {
        ft_printf_fd(2, "exit: too many arguments\n");
        free_builtin(data, pids);
        exit(1);  // Exit code 1 for too many arguments
    }

    // Handle a single argument
    if (ft_arrsize(args) == 2)
    {
        if (ft_strdigit(args[1]) == 0)
        {
            ft_printf_fd(2, "exit: numeric argument required\n");
            free_builtin(data, pids);
            exit(1);  // Exit code 1 for numeric argument error
        }
        num = ft_atol(args[1]);  // Convert argument to long
        exit_code = (int)(num % 256);  // Ensure the exit code is in the range 0-255
    }

    // Clean up and exit
    free_builtin(data, pids);
    exit(exit_code);  // Exit with the computed exit code
}