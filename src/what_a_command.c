/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_a_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoshe <gmoshe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:48:37 by gmoshe            #+#    #+#             */
/*   Updated: 2020/11/17 18:01:41 by gmoshe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void what_a_command(t_mini *mini)
{
	char	*arg;
	// if (mini->token == TO_ECHO)
	// 	do_echo(mini->args, mini->mas[0]);
	// if (mini->token == TO_EXEC)
	// 	do_exec(mini->args, mini->env, mini->command, mini->flag_pipe);
	// if (mini->token == TO_CD)
	// 	do_cd(mini->args, mini->env);
	// if (mini->token == TO_PWD)
	// 	do_pwd(mini->args, mini->env);
	// if (mini->token == TO_ENV)
	// 	print_env(mini->env);
	if (mini->token == TO_EXPORT)
		per_sred(mini, mini->args);
	if (mini->token == TO_UNSET)
		unset(mini, mini->args);
	//freeing(mini->args);
}