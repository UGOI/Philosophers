/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:01:31 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/04 19:37:53 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_all_number(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_number(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (argc == 6)
			if (argv[5][0] == '0')
				return (0);
		if (is_all_number(argv) == 1)
			return (1);
	}
	return (0);
}
