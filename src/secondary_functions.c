/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:45:45 by gmoshe            #+#    #+#             */
/*   Updated: 2020/11/16 17:04:20 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		delete(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i++;
	return (i);
}

int		ft_strper(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	**rewriting(char **exp, int delete)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (exp[i])
		i++;
	new = (char**)malloc(sizeof(char*) * (i));
	i = 0;
	while (exp[i])
	{
		if (i == delete)
			i++;
		if (exp[i])
		{
			new[j] = ft_strdup(exp[i]);
			j++;
			i++;
		}
	}
	new[j] = NULL;
	return (new);
}

char	*change_line(char *line, int delete, int addition, char *par)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (line[i] != '$')
		i++;
	new = (char*)malloc(sizeof(char) * ((ft_strlen(line) - delete) + addition));
	while (j < i)
	{
		new[j] = line[j];
		j++;
	}
	i = i + delete;
	while (*par)
	{
		new[j] = *(par++);
		j++;
	}
	while (line[i])
	{
		new[j] = line[i++];
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	delete_variable(t_mini *shell, char *line)
{
	int	i;
	char **p;

	i = -1;
	while (shell->env[++i])
	{
		if (!(ft_memcmp(line, shell->env[i], ft_strper(line, '='))))
		{
			p = shell->env;
			shell->env = rewriting(shell->env, i);//while(*shell->env)shell->env++;printf("%s\n", *(shell->env));
			freeing(p);
			break;
		}
	}
	i = -1;
	if (!shell->exp)
		return ;
	while (shell->exp[++i])
	{
		if (!(ft_memcmp(line, shell->exp[i], ft_strper(line, '='))))
		{
			p = shell->exp;
			shell->exp = rewriting(shell->exp, i);
			freeing(p);
			break;
		}
	}
}