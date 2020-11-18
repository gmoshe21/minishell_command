/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_gmoshe.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:35:06 by gmoshe            #+#    #+#             */
/*   Updated: 2020/11/18 15:44:53 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#ifndef MINISHELL_GMOSHE_H
# define MINISHELL_GMOSHE_H

void	check_export_end_environment_variable(t_mini *mini);
void	do_pwd(char **args, char **env);
void	do_echo(char **args);
void	do_cd(char **args, char **env);
void	per_sred(t_mini *shell, char **new_line);
void	unset(t_mini *shell, char **new_line);
void	delete_variable(t_mini *shell, char *line);
char	*change_line(char *line, int delete, int addition, char *par);
char	**rewriting(char **exp, int delete);
int		ft_strper(char *str, char c);
int		delete(char *str);
void	export(t_mini *shell, char **line);
int		init(t_mini *shell, char *line);
char	**check_exp(char **str, char *line);
void	print(char **str);
void	check_environment(t_mini *shell, char *str);
int		init_environment(t_mini *shell, char *str);
int		check_export(char *line);
void	freeing(char **str);
void	what_a_command(t_mini *mini);

#endif
