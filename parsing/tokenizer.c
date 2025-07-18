/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:19:54 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/12 11:31:47 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parsing.h"

static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	**tokenize(char *line, t_env *env,t_token *type)
{
	char	**tokens;
	char	**env_path;
	char	token_buf[4096];
	char	*word;
	char	*expanded;
	int		i;
	int		j;
	int		has_token;
	int		is_single;
	int		start;
	int		len;

	i = 0;
	j = 0;
	tokens = (char **) ft_malloc((sizeof(char *) * MAX_TOKENS),1);
	if (!tokens)
		return (NULL);
	env_path = list_to_array(env, NULL);
	while (line[i])
	{
		while (line[i] && is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		ft_memset(token_buf, 0, sizeof(token_buf));
		has_token = 0;
		while (line[i] && !is_space(line[i]) && !is_special_char(line[i]))
		{
			if (line[i] == '"' || line[i] == '\'')
			{
				is_single = 0;
				word = extract_quoted(line, &i, &is_single,type);
				if (!word)
				{
					print_error2("bash: syntax error near unexpected token","`newline'");
					g_exit_status = 2;
					return (NULL);
				}
				if (is_single)
					expanded = ft_strdup(word);
				else
					expanded = expand_variables(word, env_path, g_exit_status,
							0);
				ft_strcat(token_buf, expanded);
				has_token = 1;
			}
			else
			{
				start = i;
				while (line[i] && !is_space(line[i])
					&& !is_special_char(line[i]) && line[i] != '"'
					&& line[i] != '\'')
					i++;
				if (i > start)
				{
					word = ft_substr(line, start, i - start);
					expanded = expand_variables(word, env_path, g_exit_status,
							1);
					ft_strcat(token_buf, expanded);
					// free(word);
					// free(expanded);
					has_token = 1;
				}
			}
		}
		if (has_token && token_buf[0] != '\0')
			tokens[j++] = ft_strdup(token_buf);
		if (line[i] && is_special_char(line[i]))
		{
			len = 1;
			if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
					&& line[i + 1] == '>'))
				len = 2;
			tokens[j++] = ft_substr(line, i, len);
			i += len;
		}
	}
	// free_env(env_path);
	tokens[j] = NULL;
	return (tokens);
}

