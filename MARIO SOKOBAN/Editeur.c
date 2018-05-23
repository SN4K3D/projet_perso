
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_image.h>

#include "constante.h"
#include "editeur.h"
#include "fichier.h"


void editeur(SDL_Surface *ecran)
{
 	SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL, *selection = NULL, *caisse_ok = NULL;
 	SDL_Rect position, posObjetSelec;
 	SDL_Event event;

 	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
 	int objetActuel = MUR, i = 0, j = 0;
 	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};


	caisse_ok = IMG_Load("caisse_ok.jpg");
 	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	objectif = IMG_Load("objectif.png");
	mario = IMG_Load("mario_bas.gif");
	selection = IMG_Load("mur.jpg");

	if(!chargerNiveau(carte))
		exit(EXIT_FAILURE);


	 while (continuer)
	 {
	 	SDL_WaitEvent(&event);			// ouverture de l'attente d'évenement 
	 	switch(event.type)
	 	{
	 		case SDL_QUIT:
	 		continuer = 0;
	 		break;

	 		case SDL_MOUSEBUTTONDOWN:
	 			switch(event.button.button)
	 			{
	 				case SDL_BUTTON_LEFT:
	 				clicGaucheEnCours = 1;

	 				if (objetActuel == MARIO && (marioTrouve(carte) == 0) )
	 					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;

	 				else if (objetActuel != MARIO)

	 				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
	 				break;

	 				case SDL_BUTTON_RIGHT:
	 				clicDroitEnCours = 1;
	 				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
	 				break;
	 			}
	 			break;


	 			case SDL_MOUSEBUTTONUP:
	 			switch(event.button.button)
	 			{
	 				case SDL_BUTTON_LEFT:
	 				clicGaucheEnCours = 0;
	 				break;

	 				case SDL_BUTTON_RIGHT:
	 				clicDroitEnCours = 0;
	 				break;
	 			}
	 			break;

	 			case SDL_MOUSEMOTION:

	 				posObjetSelec.x = event.motion.x;
            		posObjetSelec.y = event.motion.y;
	 			
	 				if(clicGaucheEnCours)
	 				{
	 					
	 				if (objetActuel == MARIO && (marioTrouve(carte) == 0) )
	 					carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;

	 				else if (objetActuel != MARIO)
	 				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
	 				}
	 				

	 				
	 				else if(clicDroitEnCours)
	 				{
	 				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
	 				}
	 				
	 			
	 			break;

	 		case SDL_KEYDOWN:
	 			switch (event.key.keysym.sym)
	 			{
	 				case SDLK_ESCAPE:
	 				continuer = 0;
	 				break;

	 				case SDLK_s:
	 				sauvegarderNiveau(carte);
	 				break;

	 				case SDLK_c:
	 				chargerNiveau(carte);
	 				break;
	 			


		 			case SDLK_KP1:

	 				objetActuel = MUR;
	 				selection = IMG_Load("mur.jpg");
	 				break;

	 				case SDLK_KP2:
	 				objetActuel = CAISSE;
	 				selection = IMG_Load("caisse.jpg");
	 				break;

	 				case SDLK_KP3:
	 				objetActuel = OBJECTIF;
	 				selection = IMG_Load("objectif.png");
	 				break;

	 				case SDLK_KP4:
	 				objetActuel = MARIO;
	 				selection = IMG_Load("mario_bas.gif");
	 				break;


	 				case SDLK_KP5:
	 				objetActuel = CAISSE_OK;
	 				selection = IMG_Load("caisse_ok.jpg");
	 				break;

	 			}
	 			break;

	 	}
	 	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));

				

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

							case MARIO:
							SDL_BlitSurface(mario, NULL, ecran, &position);
							break;
							
							case OBJECTIF:
							SDL_BlitSurface(objectif, NULL, ecran, &position);

							case CAISSE_OK:
							SDL_BlitSurface(caisse_ok, NULL, ecran, &position);
							
							break;

							
						}
					}
				}

		SDL_BlitSurface(selection, NULL, ecran, &posObjetSelec);

		SDL_Flip(ecran);
	}

	SDL_FreeSurface(caisse_ok);
	SDL_FreeSurface(mur);
 	SDL_FreeSurface(caisse);
 	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario);


return;

}


int marioTrouve(int carte[][NB_BLOCS_HAUTEUR])
{

	int i = 0, j = 0;


	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				

				if (carte[i][j] == MARIO)
				{
					return 1;
				}
			}
		}

	return 0;
}