/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-band <hel-band@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:46:26 by hel-band          #+#    #+#             */
/*   Updated: 2024/06/26 11:46:26 by hel-band         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Characteres */
# define METACHAR "<>| "
# define VAR_BLOCK " <>|?\'\"/$"
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Lexer */
enum	e_lexeme
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BUILTIN,
	CMD,
	ARG
};

typedef struct s_exec
{
	char			**cmd;
	int				lex;
	int				fd_in;
	int				fd_out;
}			t_exec;

typedef struct t_args
{
	int		index;
	int		pipis[2];
	int		pipes[2];
}			t_args;

typedef struct s_data
{
	char	*prompt;
	char	*home;
	t_list	*env;
	t_list	*token;
	int		*lexer;
	t_exec	*exec;
	int		has_cmd;
	int		has_builtin;
	int		process_count;
	int		builtin_check;
	t_args	*args;
	int		exit_status;
	int		*fd_heredoc;
}			t_data;

void	execute(t_data *data);
void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids);
void	deal_with_pipes(t_data *data);
void	get_cmd_and_args(t_list *token, int *lexer, t_data *data);
void	finally_execute(t_data *data, int fd[], pid_t *pids);
void	close_pipes(t_args *args);
void	recycle_pipe(t_args *args);
void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids);
void	wait_all_processes(t_data *data, pid_t *pids, int flag);
void	verify_permission(char *copy, char **cmd, char **env);
int		verify(int result, char *str, char **cmd, char **env);

/* Builtin */
void	exit_builtin(t_data *data, pid_t *pids, char **args);
void	env_builtin(t_data *data, char **args);
int		pwd_builtin(t_data *data);
void	unset_builtin(t_data *data, char **args);
void	export_builtin(t_data *data, char **args);
char	**split_key_and_value(char *str, char c);
int		check_key(char *str);
void	print_export(t_list *export);
int 	echo_builtin(t_data *data, char **args);
void	cd_builtin(t_data *data, char **args);

/* Redirect */
int		validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out);
void	redirect_files(int fd_in, int fd_out);
void	close_files(int fd_in, int fd_out);
int		check_heredoc(t_data *data);

/* Free */
void	free_cmd_not_found(char **path, char **env, t_data *data, pid_t *pids);
void	free_builtin(t_data *data, pid_t *pids);
void	free_for_all(t_data *data);
void	free_list(t_list *list);
void	free_exec(t_exec *exec);

#endif

