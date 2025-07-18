/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:30:45 by eazmir            #+#    #+#             */
/*   Updated: 2025/07/09 16:31:46 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_parent_only_builtin(char *cmd)
{
	return (strcmp(cmd, "cd") == 0 || strcmp(cmd, "exit") == 0 || strcmp(cmd,
			"unset") == 0 || strcmp(cmd, "export") == 0);
}

void	validate_command(char **cmd, char **env_list)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		free_env(env_list);
		write(2, "minshell: command not found: \n", 30);
		exit(127);
	}
}

void	print_command_not_found(char **cmd)
{
	write(2, "minishell: command not found: ", 31);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n", 1);
}

void	exec(char **cmd, t_shell *shell, t_env *env, t_cmd *cmd2)
{
	char	*path;
	char	**env_list;

	(void)cmd2;
	env_list = list_to_array(env, shell);
	validate_command(cmd, env_list);
	path = check_command(cmd[0], env);
	if (!path)
	{
		print_command_not_found(cmd);
		g_exit_status = 127;
		ft_malloc(0, 0);
		exit(127);
	}
	if (execve(path, cmd, env_list) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": ", 2);
		ft_putendl_fd("Is a directory", 2);
		ft_malloc(0, 0);
		g_exit_status = 126;
		exit(126);
	}
}
