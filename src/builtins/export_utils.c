#include "minishell.h"

int	check_key(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_isalpha(str[0]) != 1 && str[0] != '_')
	{
		return (0);
	}
	return (1);
}

void	print_export(t_list *export)
{
	char	**arr;

	while (export)
	{
		arr = split_key_and_value((char *)export->content, '=');
		if (arr[1])
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		else
			printf("declare -x %s=\"\"\n", arr[0]);
		ft_free_str_arr(&arr);
		export = export->next;
	}
}