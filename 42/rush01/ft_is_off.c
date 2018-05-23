/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_off.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjolivet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:40:29 by rjolivet          #+#    #+#             */
/*   Updated: 2018/02/18 15:12:34 by rjolivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_off_line(char k, char grid[9][9], int i)
{
	int j;

	j = 0;
	while (j < 9)
	{
		if (grid[i][j] == k)
			return (0);
		j++;
	}
	return (1);
}

int		ft_off_column(char k, char grid[9][9], int j)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (grid[i][j] == k)
			return (0);
		i++;
	}
	return (1);
}

int		ft_off_block(char k, char grid[9][9], int i, int j)
{
	int		ii;
	int		jj;

	ii = i - (i % 3);
	jj = j - (j % 3);
	i = ii;
	j = jj;
	while (i < ii + 3)
	{
		while (j < jj + 3)
		{
			if (grid[i][j] == k)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
