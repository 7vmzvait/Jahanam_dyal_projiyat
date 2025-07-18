/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:03:00 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/07 14:36:44 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parent_process(t_cmd *cmd, t_context *ctx)
{
	if (ctx->prev_pipe != -1)
		close(ctx->prev_pipe);
	if (cmd->next)
		close(ctx->fdpipe[1]);
	ctx->last_pid = ctx->pids;
}

void	wait_for_children(t_context *ctx, t_cmd *cmd)
{
	int	status;

	(void)cmd;
	status = 0;
	waitpid(ctx->pids, &status, 0);
	if (ctx->detcted_syntax_error)
		return ;
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

int	execute_commands(t_cmd *cmd, t_context *ctx, t_shell *shell, t_env *env)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd)
	{
		if (cmd->next)
			pipe(ctx->fdpipe);
		ctx->pids = fork();
		if (ctx->pids == 0)
		{
			kill_process();
			child_process(cmd, ctx, shell, env);
		}
		else
			parent_process(cmd, ctx);
		if (cmd->next)
			ctx->prev_pipe = ctx->fdpipe[0];
		else
			ctx->prev_pipe = -1;
		cmd = cmd->next;
	}
	wait_for_children(ctx, cmd);
	signals_handler();
	return (g_exit_status);
}
