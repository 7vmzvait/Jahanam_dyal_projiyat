/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:35:05 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/08 09:35:09 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../parsing/parsing.h"

static void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
		exit(130);
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, SIG_IGN);
}

void	get_herdoc_line(const char *del, int *pipfd, t_cmd *cmd,
		char **env_path)
{
	char	*line;
	char	*expanded;

	(void)cmd;
	setup_heredoc_signals();
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, del, ft_strlen(del)) == 0 && ft_strlen(line)
			- 1 == ft_strlen(del))
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		expanded = expand_variables(line, env_path, 0, 0);
		write(pipfd[1], line, ft_strlen(line));
	}
	close(pipfd[1]);
	free(line);
	get_next_line(-1);
	exit(0);
}

void	_parren_process(int *pipfd, int *status, int *pid)
{
	close(pipfd[1]);
	waitpid(*pid, status, 0);
	if (WIFEXITED(*status))
		g_exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		g_exit_status = 128 + WTERMSIG(*status);
	if (g_exit_status == 0)
		dup2(pipfd[0], STDIN_FILENO);
	close(pipfd[0]);
}

void	here_doc(char *del, t_cmd *cmd, t_env *env)
{
	int		pipfd[2];
	pid_t	pid;
	int		status;
	char	**env_path;

	env_path = list_to_array(env, NULL);
	if (pipe(pipfd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		close(pipfd[0]);
		close(pipfd[1]);
		return ;
	}
	if (pid == 0)
	{
		close(pipfd[0]);
		get_herdoc_line(del, pipfd, cmd, env_path);
	}
	else
		_parren_process(pipfd, &status, &pid);
}
