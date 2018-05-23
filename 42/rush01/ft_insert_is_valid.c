/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_is_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimfeld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 15:47:12 by qgimfeld          #+#    #+#             */
/*   Updated: 2018/02/18 16:25:35 by rjolivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_off_line (char k, char grid[9][9], int i);
int		ft_off_column (char k, char grid[9][9], int j);
int		ft_off_block (char k, char grid[9][9], int i, int j);

int		ft_insert_is_valid(char grid[9][9], int position)
{
	int		i;
	int		j;
	char	k;

	i = position / 9;
	j = position % 9;
	if (position == 81)
		return (1);
	if (grid[i][j] != '0')
		return (ft_insert_is_valid(grid, position + 1));
	k = '1';
	while (k <= '9')
	{
		if (ft_off_line(k, grid, i) == 1 && ft_off_column(k, grid, j) == 1
				&& ft_off_block(k, grid, i, j) == 1)
		{
			grid[i][j] = k;
			if (ft_insert_is_valid(grid, position + 1))
				return (1);
		}
		k++;
	}
	grid[i][j] = '0';
	return (0);
}

int		ft_insert_is_valid_end(char grid[9][9], int position)
{
	int		i;
	int		j;
	char	k;

	i = position / 9;
	j = position % 9;
	if (position == 81)
		return (1);
	if (grid[i][j] != '0')
		return (ft_insert_is_valid_end(grid, position + 1));
	k = '9' + 1;
	while (k-- && k >= '1')
	{
		if (ft_off_line(k, grid, i) == 1 && ft_off_column(k, grid, j) == 1
				&& ft_off_block(k, grid, i, j) == 1)
		{
			grid[i][j] = k;
			if (ft_insert_is_valid_end(grid, position + 1))
				return (1);
		}
	}
	grid[i][j] = '0';
	return (0);
}

int		comparaison(char s1[][9], char s2[][9])
{
	int		i;
	int		j;

	i = 0;
	while (i != 9)
	{
		j = 0;
		while (j != 9)
		{
			if (s1[i][j] == s2[i][j])
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
