/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:47:42 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 10:47:44 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	infile_fd;

	if (cmd->infile)
	{
		infile_fd = open(cmd->infile, O_RDONLY);
		if (infile_fd < 0)
		{
			write(2, "minishell: ", 11);
			write(2, cmd->infile, strlen(cmd->infile));
			write(2, ": ", 2);
			perror("");
			return (-1);
		}
		return (infile_fd);
	}
	return (-1);
}

int	open_outfile(t_cmd *cmd)
{
	int	outfile_fd;

	if (cmd->outfile)
	{
		if (cmd->append == 0)
			outfile_fd = open(cmd->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			outfile_fd = open(cmd->outfile, O_CREAT | O_APPEND | O_WRONLY,
					0644);
		if (outfile_fd < 0)
		{
			perror("Error opening output file");
			return (-1);
		}
		return (outfile_fd);
	}
	return (-1);
}

int	redir_infile(t_cmd *cmd)
{
	if (!cmd || !cmd->infile)
		return (-1);
	if (cmd->infile)
	{
		cmd->fd = open_infile(cmd);
		if (cmd->fd < 0)
			return (-1);
		if (dup2(cmd->fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			return (-1);
		}
	}
	return (0);
}

int	redir_outfile(t_cmd *cmd)
{
	if (!cmd || !cmd->outfile)
		return (-1);
	if (cmd->outfile)
	{
		cmd->fd = open_outfile(cmd);
		if (cmd->fd < 0)
			return (-1);
		if (cmd->fd >= 0)
		{
			if (dup2(cmd->fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 failed");
			}
			close(cmd->fd);
		}
	}
	return (0);
}
