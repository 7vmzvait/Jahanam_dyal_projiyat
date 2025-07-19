/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:14:45 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/19 00:14:59 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	generate_file(t_cmd *cmd)
{
	int		fd;
	char	*tty;
	char	*eq;

	fd = 0;
	tty = ttyname(1);
	if (!tty)
	{
		cmd->heredoc_filename = ft_strdup("/tmp/heredoc_defoult");
		return (0);
	}
	eq = strrchr(tty, '/');
	if (!eq)
		eq = tty;
	else
		cmd->heredoc_filename = ft_strjoin("/tmp/heredoc", eq + 1);
	if (!cmd->heredoc_filename)
	{
		cmd->heredoc_filename = ft_strdup("/tmp/heredoc_defoult");
		return (0);
	}
	unlink(cmd->heredoc_filename);
	fd = open(cmd->heredoc_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	return (fd);
}

static void	heredoc_child_process(char *delimiter, t_env *env, int temp_fd)
{
	char	*line;
	size_t	delim_len;
	char	**env_arr;
	char	*expanded;

	delim_len = ft_strlen(delimiter);
	env_arr = list_to_array(env, NULL);
	setup_heredoc_signals();
	while (1)
	{
		write(STDERR_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strncmp(line, delimiter, delim_len) == 0 && line[delim_len] == '\n'
			&& line[delim_len + 1] == '\0')
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, env_arr, 0, 0);
		write(temp_fd, expanded, strlen(expanded));
		(free(expanded), free(line));
	}
	(close(temp_fd), exit(0));
}

int	heredoc_parent_process(t_cmd *cmd, int temp_fd, int pid, int status)
{
	close(temp_fd);
	waitpid(pid, &status, 0);
	
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		if (g_exit_status == 0)
		{
			cmd->here_doc_fd = open(cmd->heredoc_filename, O_RDONLY);
			if (cmd->here_doc_fd == -1)
				return (1);
			return (0);
		}
	}
	else
	{
		if (cmd->heredoc_filename)
			unlink(cmd->heredoc_filename);
		return (1);
	}
	return (1);
}

int	handle_heredoc(t_cmd *cmd, char *delimiter, t_env *env)
{
	int		temp_fd;
	int		status;
	pid_t	pid;

	status = 0;
	cmd->here_doc_fd = -1;
	temp_fd = generate_file(cmd);
	if (temp_fd == -1)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		close(temp_fd);
		return (1);
	}
	if (pid == 0)
		heredoc_child_process(delimiter, env, temp_fd);
	else
		return (heredoc_parent_process(cmd, temp_fd, pid, status));
	return (1);
}
