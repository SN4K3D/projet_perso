/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjolivet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 15:36:25 by rjolivet          #+#    #+#             */
/*   Updated: 2018/02/18 18:58:18 by rjolivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_insert_is_valid(char grid[9][9], int position);
int		ft_off_line (char k, int grid[9][9], int i);
int		ft_off_column (char k, int grid[9][9], int j);
int		ft_off_block (char k, int grid[9][9], int i, int j);
int		ft_insert_is_valid_end(char grid[9][9], int position);
int		comparaison(char s1[][9], char s2[][9]);

int		ft_strlen(char **grille)
{
	int		i;
	int		j;

	i = 1;
	while (i <= 9)
	{
		j = 0;
		while (grille[i][j])
		{
			if (grille[i][j] == '.' || grille[i][j] >= '0'
					|| grille[i][j] <= '9')
				j++;
			else if (grille[i][j] < '0' || grille[i][j] > '9')
				return (0);
		}
		i++;
	}
	return (j);
}

void	affichage(char grille[][9])
{
	int		i;
	int		j;
	char	chiffre;

	i = 0;
	while (i != 9)
	{
		j = 0;
		while (j != 9)
		{
			chiffre = (grille[i][j]);
			write(1, &chiffre, 1);
			if (j != 8)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	check_et_affiche(char tab[9][9], char tab2[9][9])
{
	if (ft_insert_is_valid(tab, 0) == 1)
	{
		if (ft_insert_is_valid_end(tab2, 0) == 1)
		{
			if (comparaison(tab, tab2) == 1)
				affichage(tab);
			else
				(write(1, "Error\n", 6));
		}
	}
	else
		(write(1, "Error\n", 6));
}

void	ft_principal(char tab[9][9], char tab2[9][9], char *argv[], int i)
{
	int		j;

	while (i < 10)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '.')
			{
				tab[i - 1][j] = '0';
				tab2[i - 1][j] = '0';
			}
			else
			{
				tab[i - 1][j] = argv[i][j];
				tab2[i - 1][j] = argv[i][j];
			}
			j++;
		}
		i++;
	}
}

int		main(int argc, char *argv[])
{
	int		i;
	char	tab[9][9];
	char	tab2[9][9];

	i = 1;
	if (argc == 10 && ft_strlen(argv) == 9)
	{
		ft_principal(tab, tab2, argv, i);
		check_et_affiche(tab, tab2);
	}
	else
		return (write(1, "Error\n", 6));
	return (0);
}
