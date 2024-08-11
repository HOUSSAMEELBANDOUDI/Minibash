/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:07:37 by hel-band          #+#    #+#             */
/*   Updated: 2024/06/26 12:07:37 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirections(char *cmd, char **envp) {
    if (strstr(cmd, ">>")) {
        char *command = strtok(cmd, ">>");
        char *filename = strtok(NULL, ">>");
        int fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execute_command(command, envp);
    } else if (strstr(cmd, ">")) {
        char *command = strtok(cmd, ">");
        char *filename = strtok(NULL, ">");
        int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execute_command(command, envp);
    } else if (strstr(cmd, "<")) {
        char *command = strtok(cmd, "<");
        char *filename = strtok(NULL, "<");
        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        execute_command(command, envp);
    } else {
        execute_command(cmd, envp);
    }
}

void handle_heredoc(char *limiter) {
    char buffer[1024];
    int temp_file = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ssize_t read_bytes;
    size_t limiter_len = strlen(limiter);

    if (temp_file < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        write(STDOUT_FILENO, "> ", 2);
        read_bytes = read(STDIN_FILENO, buffer, 1024);
        if (read_bytes < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (read_bytes == 0) {
            break;
        }
        buffer[read_bytes] = '\0';
        if (strncmp(buffer, limiter, limiter_len) == 0 && buffer[limiter_len] == '\n') {
            break;
        }
        write(temp_file, buffer, read_bytes);
    }

    close(temp_file);
}
