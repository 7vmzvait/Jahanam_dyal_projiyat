/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:34:41 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/06 09:40:53 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../parsing/parsing.h"

int		g_exit_status = 0;

void	ft_readline(t_cmd *cmd, t_shell *shell, t_context *ctx, t_env *env_var)
{
	char	*input;
	t_token	*type;

	type = (t_token *)ft_malloc(sizeof(t_token), 1);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", 1);
			ft_malloc(0, 0);
			exit(g_exit_status);
		}
		if (*input)
			add_history(input);
		cmd = parse_input(input, env_var, ctx, type);
		if (cmd && cmd->args && cmd->args[0]
			&& is_parent_only_builtin(cmd->args[0]) && cmd->pipe_to_next != 1
			&& !cmd->infile && !cmd->outfile)
			run_builtins(cmd, shell, env_var, ctx);
		else
			execute_commands(cmd, ctx, shell, env_var);
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmd		*cmd;
	t_context	*ctx;
	t_shell		*shell;
	t_env		*env_var;

	(void)argc;
	(void)argv;
	cmd = NULL;
	ctx = (t_context *)ft_malloc(sizeof(t_context), 1);
	shell = (t_shell *)ft_malloc(sizeof(t_shell), 1);
	env_var = init_env(env);
	ctx->prev_pipe = -1;
	ctx->pids = -1;
	signals_handler();
	ft_readline(cmd, shell, ctx, env_var);
	ft_malloc(0, 0);
}
