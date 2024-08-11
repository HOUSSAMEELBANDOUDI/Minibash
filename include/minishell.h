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

#endif

