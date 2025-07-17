/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:21:26 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/26 12:21:31 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	free_key3(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
	return (0);
}

char	*parse_key_value(char *args, char **key, char **value)
{
	char	*eq;
	int		len;

	eq = ft_strchr(args, '=');
	if (eq)
	{
		len = eq - args;
		*key = ft_substr_2(args, 0, len);
		if (!*key)
		{
			free(*key);
			return (NULL);
		}
		*value = ft_strdup_2(eq + 1);
		if (!*value)
			return (free_key3(*key, *value), NULL);
	}
	else
	{
		*key = ft_strdup_2(args);
		*value = NULL;
	}
	return (eq);
}

char	*handle_extraction_option(char *key, char *value, char opt)
{
	if (!value && opt != 'V')
		return (ft_strdup_2(key));
	else if (!value && opt == 'V')
		return (NULL);
	if (opt == 'V')
	{
		free(key);
		return (value);
	}
	if (opt == 'K')
	{
		free(value);
		return (key);
	}
	free(key);
	free(value);
	return (NULL);
}

char	*extract_args(char *args, char opt)
{
	char	*key;
	char	*value;
	char	*eq;

	eq = parse_key_value(args, &key, &value);
	if (!key)
		return (NULL);
	return (handle_extraction_option(key, value, opt));
}
