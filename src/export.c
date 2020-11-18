/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:37:16 by gmoshe            #+#    #+#             */
/*   Updated: 2020/11/16 14:27:56 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print(char **str)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	while (str[i])
	{
		j = 0;
		x = 1;
		write(1, "declare -x ", 11);
		while (str[i][j])
		{
			if(str[i][j - 1] && str[i][j - 1] == '=' && x)
			{
				write(1, "\"", 1);
				x = 0;
			}
			write(1, &str[i][j], 1);
			j++;
		}
		if(!x)
			write(1, "\"\n", 2);
		 else
		 	write(1, "''\n", 4);
		i++;
	}
	return ;
}

int		check_export(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (0);
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**check_exp(char **str, char *line)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
	{
		new = (char**)malloc(sizeof(char*) * (2));
		new[0] = ft_strdup(line);
		new[1] = NULL;
		return (new);
	}
	while (str[i])
		i++;
	new = (char**)malloc(sizeof(char*) * (i + 2));
	while (str[j])
	{
		new[j] = ft_strdup(str[j]);
		j++;
	}
	new[j] = ft_strdup(line);
	new[++j] = NULL;
	if (str)
		freeing(str);
	return (new);
}

int		init(t_mini *shell, char *line)
{
	int	i;
	char	j;

	i = 0;
	j = '=';
	if (!(ft_strchr(line, '=')))
		j = '\0';
	if (!shell->exp)
		return (0);//printf("%s\n", line);
	while (shell->exp[i])
	{
		if(!(ft_memcmp(line, shell->exp[i], ft_strper(line, j))))
			{
				if (j == '\0')
					return (1);
				free(shell->exp[i]);
				shell->exp[i] = ft_strdup(line);
				return (1);
			}
		i++;
	}
	return (0);
}

void	export(t_mini *shell, char **new_line)
{
	char	*str;
//	char	**new_line;
	int		i;

	//new_line = ft_split(line, ' ');//printf("|%s|\n", *new_line);
	i = 0;//printf("1\n");
	while (new_line[i])
	{
		if(!(init(shell, new_line[i])))
			shell->exp = check_exp(shell->exp, new_line[i]);
		i++;
	}
	i = 0;
	while (new_line[i])
	{
		if (ft_strchr(new_line[i], '='))
			init_environment(shell, new_line[i]);
		i++;
	}
	
}