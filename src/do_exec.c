#include "../minishell.h"

char		*join(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	stot_len;
	char	*rtn;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	stot_len = s1_len + s2_len + 1;
	rtn = malloc(sizeof(char) * stot_len);
	if (!rtn)
		return (0);
	ft_memmove(rtn, s1, s1_len);
	ft_memmove(rtn + s1_len, s2, s2_len);
	rtn[stot_len - 1] = '\0';
	free((char *)s1);
	return (rtn);
}

char **search_for_path(char **env)
{
	char	**double_ptr;
	char	*pointer;
	char	*ptr;
	int		i;
	
	i = 0;
	double_ptr = env;
	while (double_ptr++)
	{
		ptr = *double_ptr;
		if (ft_strncmp(ptr, "PATH", 4) == 0)
		{
			ptr = ft_strdup(ptr);
			pointer = ptr;
			while (ptr[i] != '/')
				i++;
			ptr = ft_substr(ptr, i, ft_strlen(ptr) - i);
			free(pointer);
			pointer = ptr;
			double_ptr = ft_split(ptr, ':');
			free(pointer);
			return (double_ptr);
		}
	}
	return (NULL);
}

char	*search_for_dir(char **env, char **argv, char *command)
{
	DIR				*ptr;
	struct dirent	*entry;
	char			*ret_str;
	char			**str = search_for_path(env);
	int				i;

	i = -1;
	while ((ptr = opendir(str[++i])))
	{
		while ((entry = readdir(ptr)) != NULL)
		{
			if (ft_strncmp(command, entry->d_name, ft_strlen(entry->d_name)) == 0)
			{
				str[i] = join(str[i], "/");
				ret_str = ft_strjoin(str[i], command);
				freeing(str);
				return (ret_str);
			}
		}
		myclosedir(entry);
		free(ptr);
	}
	freeing(str);
	return ("ptr");
}

void	do_exec(char **args, char **env, char *command, int flag)
{
	pid_t pid;
	char **argv;//printf("%s|%s|%d||||\n", *args, *(args+1), flag);
	int x;
	x = 0;

	// argv = ft_calloc(ft_lstsize(mini->l_ptr) + 1, sizeof(char**));
	// while (mini->l_ptr != NULL)
	// {
	// 	argv[x] = ft_strdup(mini->l_ptr->content);
	// 	ft_lstdelone(mini->l_ptr, free);
	// 	mini->l_ptr = mini->l_ptr->next;
	// 	x++;
	// }
	char *file = search_for_dir(env, args, command);
	if (flag == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(file, args, env);
		}
		waitpid(pid, NULL, WUNTRACED);
	}
	else
	{
		execve(file, args, env);
		waitpid(pid, NULL, WUNTRACED);
	}
	free(file);
}
