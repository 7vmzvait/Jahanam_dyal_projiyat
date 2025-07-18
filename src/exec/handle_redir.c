/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:29:14 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:50:39 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_1(t_cmd *cmd, char **tokens, int *i)
{
	(void)tokens;
	(*i)++;
	cmd->heredoc = 1;
}

void	handle_append(t_cmd *cmd, char **tokens, int *i)
{
	int	fd;

	if (cmd->outfile)
	{
		if (cmd->append == 0)
			fd = open(cmd->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd >= 0)
			close(fd);
		free(cmd->outfile);
	}
	cmd->outfile = ft_strdup(tokens[++(*i)]);
	cmd->append = 1;
}

void	check_redir(t_cmd *cmd, char **tokens, int *i)
{
	int	fd;

	if (!ft_strcmp(tokens[*i], "<"))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(tokens[++(*i)]);
	}
	else if (!ft_strcmp(tokens[*i], ">"))
	{
		if (cmd->outfile)
		{
			fd = open(cmd->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (fd >= 0)
				close(fd);
			free(cmd->outfile);
		}
		cmd->outfile = ft_strdup(tokens[++(*i)]);
		cmd->append = 0;
	}
	else if (!ft_strcmp(tokens[*i], ">>"))
		handle_append(cmd, tokens, i);
	else if (!ft_strcmp(tokens[*i], "<<"))
		handle_heredoc_1(cmd, tokens, i);
}

int	is_redir(char *tokens)
{
	return (!ft_strcmp(tokens, ">") || !ft_strcmp(tokens, ">>")
		|| !ft_strcmp(tokens, "<") || !ft_strcmp(tokens, "<<"));
}

void	handle_redir2(t_cmd *cmd, char **tokens, int *i)
{
	if (tokens[*i])
		check_redir(cmd, tokens, i);
}
