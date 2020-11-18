#include "../minishell.h"

// char **search_for_path(t_mini *mini)
// {
// 	char **double_ptr;
// 	char *ptr;
// 	int i;
	
// 	i = 0;
// 	double_ptr = mini->env;
// 	while (double_ptr++)
// 	{
// 		ptr = *double_ptr;
// 		if (ft_strncmp(ptr, "PATH", 4) == 0)
// 		{
// 			ptr = ft_strdup(ptr);
// 			while (ptr[i] != '/')
// 				i++;
// 			ptr = ft_substr(ptr, i, ft_strlen(ptr) - i);
// 			double_ptr = ft_split(ptr, ':');
// 			return (double_ptr);
// 		}
// 	}
// 	return (NULL);
// }

// char	*search_for_dir(t_mini *mini, char **argv)
// {
// 	DIR *ptr;
// 	struct dirent *entry;
// 	char *ret_str;
// 	char **str = search_for_path(mini);
// 	int i = 0;
// 	while ((ptr = opendir(str[i])))
// 	{
// 		ptr = opendir(str[i]);
// 		while ((entry = readdir(ptr)) != NULL)
// 		{
// 			if (ft_strncmp(argv[0], entry->d_name, ft_strlen(entry->d_name)) == 0)
// 			{
// 				str[i] = ft_strjoin(str[i], "/");
// 				ret_str = ft_strjoin(str[i], argv[0]);
// 				return (ret_str);
// 			}
// 		}
// 		i++;
// 	}
// 	return ("ptr");
// }

// void	do_exec(t_mini *mini)
// {
// 	pid_t pid;
// 	char **argv;
// 	int x;
// 	x = 0;

// 	argv = ft_calloc(ft_lstsize(mini->l_ptr) + 1, sizeof(char**));
// 	while (mini->l_ptr != NULL)
// 	{
// 		argv[x] = ft_strdup(mini->l_ptr->content);
// 		ft_lstdelone(mini->l_ptr, free);
// 		mini->l_ptr = mini->l_ptr->next;
// 		x++;
// 	}
// 	char *file = search_for_dir(mini, argv);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(file, argv, mini->env);
// 	}
// 	waitpid(pid, NULL, WUNTRACED);
// }

// void	search_args(t_mini *mini)
// {
// 	t_dblcon *ptr;

// 	int i;
// 	int res;
// 	i = 0;
// 	res = 0;
// 	mini->args = ft_calloc(mini->def->size + 2, sizeof(char**));
// 	while (mini->d_lst && ft_strncmp(mini->d_lst->content, "|", 2) != 0)
// 	{
// 		while (mini->d_lst && ft_strncmp(mini->d_lst->content, ">", 2) == 0)
// 		{
// 			mini->d_lst = mini->d_lst->next->next;
// 			res++;
// 		}
// 		if(!mini->d_lst)
// 		{
// 			mini->d_lst = mini->def->tail;
// 			break ;
// 		}
// 		if (ft_strncmp(mini->d_lst->content, "|", 2) == 0)
// 			break ;
// 		mini->args[i] = ft_strdup(mini->d_lst->content);
// 		// printf("%s\n", mini->args[i]);
// 		mini->d_lst = mini->d_lst->next;
// 		i++;
// 	}
// 	ptr = mini->d_lst;	// тут мы на пайпе
// 	if (mini->d_lst && ft_strncmp(mini->d_lst->content, "|", 2) == 0)
// 		mini->re_flag = 1;
// 	if (!mini->d_lst && mini->re_flag != 1)
// 		mini->d_lst = mini->def->tail;
// 	while (mini->d_lst)
// 	{
// 		if (ft_strncmp(mini->d_lst->content, ">", 2) == 0)
// 		{
// 			mini->d_lst = mini->d_lst->next;
// 			mini->fd_re = open(mini->d_lst->content, O_CREAT | O_WRONLY | O_APPEND, 0666);
// 			do_redir(mini);
// 			if (mini->re_flag == 0)
// 				ft_bzero(mini->args, mini->def->size + 2);
// 			break;
// 			// mini->d_lst = mini->d_lst->next;
// 			// printf("%s\n", mini->d_lst->next->content);
// 			check_for_command(mini);
// 		}
// 		if (mini->d_lst)
// 			mini->d_lst = mini->d_lst->prev;
// 	}
// 	mini->d_lst = ptr;
// 	if (mini->d_lst)
// 	{
// 		if (ft_strncmp(mini->d_lst->content, "|", 2) == 0 && mini->d_lst)
// 		{
// 			// while (ft_strncmp(mini->d_lst->content, ">", 2) != 0)
// 			// {

// 			// }
// 			do_pipe(mini);
// 			ft_bzero(mini->args, mini->def->size + 2);
// 			mini->d_lst = mini->d_lst->next;
// 			// if (mini->re_flag == 0)
// 			// 	return ;
// 			// mini->re_flag = 0;
// 			check_for_command(mini);
// 		}
// 	}
// }

int check_for_command(t_mini *mini)
{
	if (!mini->d_lst)
		return (1);
	int i = 0;
	pars(mini);
	if (ft_strncmp(mini->d_lst->content, "echo", 5) == 0)
		mini->token = TO_ECHO;
		// do_echo(mini);
	else if (mini->d_lst == NULL)
		return (1);
	else if (ft_strncmp(mini->d_lst->content, "cd", 3) == 0)
		mini->token = TO_CD;
		// do_cd(mini);
	else if (ft_strncmp(mini->d_lst->content, "pwd", 4) == 0)
		mini->token = TO_PWD;
		// do_pwd(mini);
	else if (ft_strncmp(mini->d_lst->content, "export", 7) == 0)
		mini->token = TO_EXPORT;
	else if (ft_strncmp(mini->d_lst->content, "unset", 6) == 0)
		mini->token = TO_UNSET;
	else if (ft_strncmp(mini->d_lst->content, "env", 4) == 0)
		mini->token = TO_ENV;
	else if (ft_strncmp(mini->d_lst->content, "exit", 5) == 0)
		exit(0);
	else
	{
		mini->command = ft_strdup(mini->d_lst->content);
		mini->token = TO_EXEC;
	}
	// search_args(mini);
	return (0);
	// do_exec(mini->args, mini->env, mini->command);
}