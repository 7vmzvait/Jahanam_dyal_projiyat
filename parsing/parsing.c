/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:31:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/07 15:24:34 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parsing.h"

t_cmd *parse_input(char *input,t_env *env,t_context *ctx)

{
	char	**tokens;
	t_cmd	*cmds;

	ctx->detcted_syntax_error = false;
	tokens = tokenize(input, env);
	if (!tokens)
	{
		// free_tokens(tokens);
		// g_exit_status = 127;
		return (NULL);
	}
	if (check_syntax_error(tokens))
	{
		// free_tokens(tokens);
		g_exit_status = 2;
		ctx->detcted_syntax_error = true;
		return (NULL);
	}
	cmds = parse_tokens1(tokens);
	// free_tokens(tokens);
	return (cmds);
}