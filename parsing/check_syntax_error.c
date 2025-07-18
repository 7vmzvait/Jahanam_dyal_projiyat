/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:03:44 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/06 09:40:36 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../include/minishell.h"

void	print_error2(const char *prefix, const char *name)
{
	write(2, "minishell: ", 11);
	if (prefix)
	{
		write(2, prefix, ft_strlen(prefix));
		write(2, ": ", 2);
	}
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, "\n", 2);
	}
}

int	check_syntax_error(char **tokens ,t_token *type)
{
	int i = 0;

	if (!tokens || !tokens[0])
		return (1);

	if (!ft_strcmp(tokens[0], "|"))
	{
		print_error2("bash: syntax error near unexpected token", "`|`");
		return (1);
	}

	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "|") && tokens[i + 1] && !ft_strcmp(tokens[i
				+ 1], "|"))
		{
			print_error2("bash: syntax error near unexpected token", "`||`");
			return (1);
		}
		if ((!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], "<<") || !ft_strcmp(tokens[i], ">>")) &&  !type->flags && (!tokens[i + 1] || is_special(tokens[i + 1][1])))
		{
			print_error2("bash: syntax error near unexpected token",
				"`newline'");
			return (1);
		}
		i++;
	}
	// if (i > 0 && !ft_strcmp(tokens[i - 1], "|"))
	// if (i > 0 && !ft_strcmp(tokens[i], "|") && tokens[i - 1] && !ft_strcmp(tokens[i-1], "\""))
	// {
	// 	printf("am here");
	// 	//print_error2("bash: syntax error near unexpected token", "`|`");
	// 	return (1);
	// }
	return (0);
}