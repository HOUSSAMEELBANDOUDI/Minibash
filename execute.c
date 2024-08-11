/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:04:17 by hel-band          #+#    #+#             */
/*   Updated: 2024/06/26 12:04:17 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(char *cmd, char **envp) {
    char **args = ft_split(cmd, ' ');
    if (execve(args[0], args, envp) == -1) {
        perror("execve");
    }
    ft_split_free(args);
}

void parse_and_execute(char *line, char **envp) {
    if (strncmp(line, "cd", 2) == 0 || strncmp(line, "exit", 4) == 0 || strncmp(line, "pwd", 3) == 0 ||
        strncmp(line, "echo", 4) == 0 || strncmp(line, "export", 6) == 0 || strncmp(line, "unset", 5) == 0 ||
        strncmp(line, "env", 3) == 0) {
        handle_builtin(line);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            handle_redirections(line, envp);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
        } else {
            waitpid(pid, NULL, 0);
        }
    }
}
