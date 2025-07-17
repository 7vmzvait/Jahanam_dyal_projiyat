/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:12:52 by eazmir            #+#    #+#             */
/*   Updated: 2024/11/20 22:38:02 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../parsing/parsing.h"

char	*ft_strdup_2(const char *s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}



char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	ptr = (char *)ft_malloc((len + 1) * sizeof(char),1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
