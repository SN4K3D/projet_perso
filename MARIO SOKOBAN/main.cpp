
/* main.c 

Role : Menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.

 */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_image.h>

#include "constante.h"
#include "jeu.h"
#include "editeur.h"




int main(int argc, char **argv)
{

	int continuer = 1;

	SDL_Surface *ecran = NULL, *menu = NULL;
	SDL_Event event;
	SDL_Rect posMenu;


	


	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		 fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
	

     exit(EXIT_FAILURE);
 	}


	SDL_WM_SetIcon(IMG_Load("icon.png"),NULL);

	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	SDL_WM_SetCaption("Mario Sokoban By SNAKE !", NULL);

	menu = IMG_Load("menu.jpg");
	posMenu.x = 0;
	posMenu.y = 0;

	




 while (continuer)
 {
 	SDL_WaitEvent(&event);
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

 				case SDLK_KP1:
 				jouer (ecran, continuer);
 				break;

 				case SDLK_KP2:
 				editeur(ecran);
 				break;
 			
 			}


	break;
 }

 	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));

 	SDL_BlitSurface(menu, NULL, ecran, &posMenu);
 	SDL_Flip(ecran);
 }
 

/*if (SDL_Init(SDL_INIT_VIDEO) == -1);
 {

     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",SDL_GetError());

     exit(EXIT_FAILURE);
 }
*/

SDL_FreeSurface(menu);


SDL_Quit();

return EXIT_SUCCESS;
}