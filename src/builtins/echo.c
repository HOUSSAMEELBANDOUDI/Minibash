#include "minishell.h"

static void print_new_line(int n_check);
static int verify_n(char *str);

void echo_builtin(t_data *data, char **args)
{
    int i = 1;
    int n_check = 0;

    // Check for the "-n" option
    while (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0 && verify_n(args[i]))
    {
        n_check = 1;
        i++;
    }

    // Print the rest of the arguments
    while (args[i] != NULL)
    {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }

    // Print new line if not suppressed
    print_new_line(n_check);

    data->exit_status = 0;
}

void print_new_line(int n_check)
{
    if (n_check == 0)
        printf("\n");
}

static int verify_n(char *str)
{
    int i = 1;  // Start checking after the first dash

    // Check if all characters after the dash are 'n'
    while (str[++i] != '\0')
    {
        if (str[i] != 'n')
            return 0;
    }
    return 1;
}
