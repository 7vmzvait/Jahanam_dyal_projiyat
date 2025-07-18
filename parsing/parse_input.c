/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:23:10 by haitaabe          #+#    #+#             */
/*   Updated: 2025/06/27 16:41:16 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parsing.h"

t_cmd *parse_tokens1(char **tokens, t_env *env,t_token *type)
{
    t_cmd *cmd_list = NULL;
    t_cmd *cmd = NULL;
    int i = 0;

    while (tokens[i]) 
    {
       if (!cmd_list)
       {
			cmd = new_cmd_node();
			if (!cmd)
				return (NULL);
			cmd_list = cmd;
		}
		if (!ft_strcmp(tokens[i], "|") && !type->flags)
		{
            cmd->pipe_to_next = 1;
			cmd = new_cmd_node();
			if (!cmd)
			{
                return (NULL);
			}
			add_cmd_to_list(&cmd_list, cmd);
			i++;
			continue ;
		}
        else if ((!ft_strcmp(tokens[i], "<<"))  && (!type->flags)) 
		{
            handle_redir2(cmd, tokens, &i);
            cmd->heredoc = 1;
            
            if (handle_heredoc(cmd, tokens[i], env) != 0)
                return (NULL);
            i++;
            continue;
        }
        else if ((!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") ||  !ft_strcmp(tokens[i], ">>"))  && !type->flags) {
            handle_redir2(cmd, tokens, &i);
            i++;
            continue;
        }
        else{
            add_arg_to_cmd(cmd, ft_strdup(tokens[i]));
        }
        i++;
    }
    return cmd_list;
}
