/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export_end_environment_variable.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:12:11 by gmoshe            #+#    #+#             */
/*   Updated: 2020/11/18 16:06:31 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_line(char *str)
{
	int		i;
	int		x;
	char	*new;
	
	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			x++;
		i++;
	}
	if (x % 2 != 0)
		x--;
	new = (char*)malloc(sizeof(char) * (++i - x));
	i = 0;
	while (*str)
	{
		while(*str == '\"' && x)
		{
			str++;
			x--;
		}
		if (*str)
		{
			new[i] = *str;
			i++;
			str++;
		}
		new[i] = '\0';
	}
	return (new);
}

char	*expi(t_mini *shell, char *line)
{
	int		i;
	int		x;
	int		j;
	char	*check_per;

	i = -1;
	while((check_per = ft_strchr(line, '$')))
	{
		x = delete(check_per + 1) + 1;
		while(shell->exp[++i])
			{
				if (!(ft_memcmp(check_per + 1, shell->exp[i], ft_strper(check_per, ' ') - 1)))
				{
					j = ft_strlen(shell->exp[i]) - (ft_strper(line, '='));
					line = change_line(line, x, j, shell->exp[i] + ft_strper(check_per, ' '));
					break;
				}
			}
	}
	return (line);
}

void	per_sred(t_mini *shell, char **new_line)
{
//	char	**new_line;
	int		i;

	i = 0;
	//line += 6;
	// while (*new_line == ' ')
	// 	line++;
	if (new_line[0] == NULL)
	{
		print(shell->env);
		freeing(new_line);
		return ;
	}
	export(shell, new_line);
	//new_line = ft_split(line, ' ');
	while(new_line[i])
		check_environment(shell, new_line[i++]);
	freeing(new_line);
}

void	unset(t_mini *shell, char **new_line)
{
	//char	**new_line;
	int		i;

	i = 0;
	//new_line = ft_split(line, ' ');
	while (new_line[i])
		delete_variable(shell, new_line[i++]);
	freeing(new_line);
}

void	check_export_end_environment_variable(t_mini *mini)
{
	//mini->line = new_line(mini->line);
	if (ft_strchr(mini->line, '$'))
		mini->line = expi(mini, mini->line);
	// if (ft_strnstr(mini->line, "export", 6))
	// 	per_sred(mini, mini->line);
	// if (ft_strnstr(mini->line, "unset", 5))
	// 	unset(mini, mini->line);
	// if	(check_export(mini->line))
	// 	export(mini, mini->line);
}