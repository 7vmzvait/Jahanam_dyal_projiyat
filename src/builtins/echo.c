/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:52:23 by eazmir            #+#    #+#             */
/*   Updated: 2025/06/30 18:07:35 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void malti_line_skip(char **args, int *i, bool *newline)
{
    while (args[*i])
    {
        if (ft_strncmp(args[*i], "-n", 2) == 0)
        {
            (*i)++;
            *newline = false;
        }
        else
            break;
    }
}
int    ft_echo(char **args)
{
    int i;
    bool    newline;

    newline = true;
    i = 1;
    if (!args[1])
	{
		write(1,"\n",1);
        return (g_exit_status);
	}
    malti_line_skip(args,&i,&newline);
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    return (g_exit_status);
}
