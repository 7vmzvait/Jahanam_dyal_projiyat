/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:23:51 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/06 10:02:31 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	free_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	if (!tokens)
// 		return ;
// 	while (tokens[i])
// 	{
// 		free(tokens[i]);
// 		i++;
// 	}
// 	free(tokens);
// }

// void	free_cmds(t_cmd *head)
// {
// 	t_cmd	*tmp;

// 	while (head)
// 	{
// 		tmp = head;
// 		if (tmp->args)
// 			free_tokens(tmp->args);
// 		if (tmp->infile)
// 			free(tmp->infile);
// 		if (tmp->outfile)
// 			free(tmp->outfile);
// 		head = head->next;
// 		free(tmp);
// 	}
// }
// void	free_token_list(t_token *tokens)
// {
// 	t_token *tmp;
// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		if (tokens->value)
// 			free(tokens->value);
// 		free(tokens);
// 		tokens = tmp;
// 	}
// }