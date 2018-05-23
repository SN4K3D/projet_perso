
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_image.h>


#include "constante.h"
#include "jeu.h"







void jouer(SDL_Surface *ecran)
{
	// Déclaration de mes variables

	int objectifsRestants = 0, i = 0, j = 0, continuer = 1;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

	SDL_Event event;
	SDL_Surface *mur = NULL, *mario = NULL, *caisse = NULL, *caisse_ok = NULL, *objectif = NULL;


	// Initialisation et déclaration de mes positions

	SDL_Rect posMario, position;


	// chargement des sprites ( décors et personnages)

	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	caisse_ok = IMG_Load("caisse_ok.jpg");
	objectif = IMG_Load("objectif.png");
	mario = IMG_Load("mario_bas.gif");
	//SDL_SetColorKey(mario, SDL_SRCCOLORKEY, SDL_MapRGB(mario->format, 255, 255, 255));

	// chargement du niveau 


	if (!chargerNiveau(carte))

	{
		printf("Probleme de chargement\n");
		exit(EXIT_FAILURE); 	// on arrete le jeu si on n'a pas pu charger le niveau
	}

		// recherche de la position de Mario au départ
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for(j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				if (carte[i][j] == MARIO)
				{
					posMario.x = i;
					posMario.y = j;
					carte[i][j] = VIDE;
				}
			}
		}


	
	SDL_EnableKeyRepeat(100, 100);		// commande de répétition pour les touche du clavié enfoncé

	 while (continuer)
	 {
	 	SDL_WaitEvent(&event);			// ouverture de l'attente d'évenement 
	 	switch(event.type)
	 	{
	 		case SDL_QUIT:
	 		continuer = 0;
	 		break;

	 		case SDL_KEYDOWN:
	 			switch (event.key.keysym.sym)
	 			{
	 				case SDLK_ESCAPE:
	 				continuer = 0;
	 				break;

	 				case SDLK_UP:
	 				mario = IMG_Load("mario_haut.gif");
	 				deplacerJoueur(carte, &posMario, HAUT);
	 				break;

	 				case SDLK_DOWN:
	 				mario = IMG_Load("mario_bas.gif");
	 				deplacerJoueur(carte, &posMario, BAS);
	 				break;

	 				case SDLK_RIGHT:
	 				mario = IMG_Load("mario_droite.gif");
	 				deplacerJoueur(carte, &posMario, DROITE);
	 				break;

	 				case SDLK_LEFT:
	 				mario = IMG_Load("mario_gauche.gif");
	 				deplacerJoueur(carte, &posMario, GAUCHE);
	 				break;

	 			}
	 			break;

	 	}
				SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));

				objectifsRestants = 0;

				for (i = 0; i < NB_BLOCS_LARGEUR; i++)
				{
					for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
					{
						position.x = i * TAILLE_BLOC;
						position.y = j * TAILLE_BLOC;

						switch(carte[i][j])
						{
							case MUR:
							SDL_BlitSurface(mur, NULL, ecran, &position);
							break;

							case CAISSE:
							SDL_BlitSurface(caisse, NULL, ecran, &position);
							break;

							case CAISSE_OK:
							SDL_BlitSurface(caisse_ok, NULL, ecran, &position);
							break;

							case OBJECTIF:
							SDL_BlitSurface(objectif, NULL, ecran, &position);
							objectifsRestants = 1;
							break;

							
						}
					}
				}

				if (!objectifsRestants)
					continuer = 0;

				position.x = posMario.x * TAILLE_BLOC;
				position.y = posMario.y * TAILLE_BLOC;

			 	SDL_BlitSurface(mario, NULL, ecran, &position);


			 	SDL_Flip(ecran);



	 }
	 	

 	SDL_EnableKeyRepeat(0,0);		//désactivation de la répétition de touches

 	SDL_FreeSurface(mur);
 	SDL_FreeSurface(caisse);
 	SDL_FreeSurface(caisse_ok);
 	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario);

	 	


}


void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
	switch (direction)
	{
		case HAUT:
		if (pos->y - 1 < 0)
			break;

		if (carte[pos->x][pos->y - 1] == MUR) // s'il y a un mur on stop
			break;

		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK ) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK ))
			break;

		// arriver a ce stade c'est qu'on peut déplacer le joueur
		//on va d'abord vérifier s'il y a une caisse a déplacer

		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--; //on fait monter le joueur
		break;



		case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;

		if (carte[pos->x][pos->y + 1] == MUR) // s'il y a un mur on stop
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK ) &&
			(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK ))
			break;

		// arriver a ce stade c'est qu'on peut déplacer le joueur
		//on va d'abord vérifier s'il y a une caisse a déplacer

		deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		break;


		case GAUCHE:
		if (pos->x - 1 < 0)
			break;

		if (carte[pos->x -1 ][pos->y] == MUR) // s'il y a un mur on stop
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK ) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK ))
			break;

		// arriver a ce stade c'est qu'on peut déplacer le joueur
		//on va d'abord vérifier s'il y a une caisse a déplacer

		deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		break;


		case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;

		if (carte[pos->x +1 ][pos->y] == MUR) // s'il y a un mur on stop
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK ) &&
			(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR || carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK ))
			break;

		// arriver a ce stade c'est qu'on peut déplacer le joueur
		//on va d'abord vérifier s'il y a une caisse a déplacer

		deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		break;

	}
}






void deplacerCaisse (int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;

		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}



	
}
