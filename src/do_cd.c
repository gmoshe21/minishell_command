#include "../minishell.h"

char *get_pwd(char **env)
{
	char	*str;
	char	*pointer;

	while (*env++)
	{
		str = ft_strdup(*env);
		pointer = str;
		if (ft_strncmp(str, "HOME", 4) == 0)
		{
			str = ft_substr(str, 5, ft_strlen(str));
			free(pointer);
			return (str);
		}
		free(pointer);
	}
	return (NULL);
}

void	do_cd(char **args, char **env)
{
	char	*str;

	if (args[1])
		chdir(args[1]);
	else
	{
		str = get_pwd(env);
		chdir(str);
		free(str);
	}
}