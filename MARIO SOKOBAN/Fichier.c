#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_image.h>



#include "constante.h"
#include "fichier.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
	FILE* fichier = NULL;
	SDL_Event event;
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
	int i = 0, j = 0, continuer = 1;

	//fichier = fopen("niveaux.1", "r");
	

while(continuer)
{
	SDL_WaitEvent(&event);			// ouverture de l'attente d'évenement 
	 	switch(event.type)
	 	{
	 		

	 		case SDL_KEYDOWN:
	 			switch (event.key.keysym.sym)
	 			{
	 				case SDLK_ESCAPE:
	 				continuer = 0;
	 				break;


	 				case SDLK_KP1:
	 				fichier = fopen("niveaux.1", "r");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP2:
	 				fichier = fopen("niveaux.2", "r");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP3:
	 				fichier = fopen("niveaux.3", "r");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP4:
	 				fichier =fopen("niveaux.4", "r");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP5:
	 				fichier = fopen("niveaux.5", "r");
	 				continuer = 0;
	 				break;

	 			}
	 			break;
	 			

		}

	}



if (fichier == NULL)
		return 0;


	fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			switch(ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
			{
				case '0':
				niveau[j][i] = 0;
				break;

				case '1':
				niveau[j][i] = 1;
				break;

				case '2':
				niveau[j][i] = 2;
				break;

				case '3':
				niveau[j][i] = 3;
				break;

				case '4':
				niveau[j][i] = 4;
				break;
			}
		}
	}

fclose(fichier);
	return 1;

}



int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
	SDL_Event event;
	FILE *fichier = NULL;
	int i = 0, j = 0, lvl = 0, continuer = 1;



while(continuer)
{
	SDL_WaitEvent(&event);			// ouverture de l'attente d'évenement 
	 	switch(event.type)
	 	{
	 		

	 		case SDL_KEYDOWN:
	 			switch (event.key.keysym.sym)
	 			{
	 				case SDLK_ESCAPE:
	 				continuer = 0;
	 				break;


	 				case SDLK_KP1:
	 				fichier = fopen("niveaux.1", "w");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP2:
	 				fichier = fopen("niveaux.2", "w");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP3:
	 				fichier = fopen("niveaux.3", "w");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP4:
	 				fichier =fopen("niveaux.4", "w");
	 				continuer = 0;
	 				break;

	 				case SDLK_KP5:
	 				fichier = fopen("niveaux.5", "w");
	 				continuer = 0;
	 				break;

	 			}
	 			break;
	 			

		}

	}







	
	if (fichier == NULL)
		return 0;

	for (i = 0 ; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			fprintf(fichier, "%d", niveau[j][i]);
		}
	}


	fclose(fichier);
	return 1;
}