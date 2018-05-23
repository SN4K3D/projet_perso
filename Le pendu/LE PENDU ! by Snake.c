#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char lireCaractere()
{
    char caractere = 0;

    caractere = getchar();
    caractere = toupper(caractere);

    while (getchar() != '\n');

    return caractere;
}




void rechercheMotSecret(FILE *dico, char secret[20])
{
    int MAX = 0,MIN = 1,motSecret = 0, caractereLu = 0;

    while(1)
    {
        if (fgetc(dico) == '\n')
        MAX ++;

        if (feof(dico))
            break;
    }
    rewind(dico);

    srand(time(NULL));
    motSecret = (rand() % MAX) ;
    printf("%d ", motSecret);
    while (motSecret > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            motSecret --;
    }

    fgets(secret, 20, dico);
}


int rechercheLettre (char maLettre, int lettreTrouvee[],char secret[])
{
    int i=0, bonneLettre = 0;

    for (i=0;secret[i] != '\0';i++)
    {
        if (maLettre == secret[i])
        {
            bonneLettre = 1;
            lettreTrouvee[i] = 1;
            printf("\n Bravo tu a Trouve une des lettre du mot secret !!");
        }
    }
     return bonneLettre;
}

int gagne (int lettreTrouvee[], int tailleMot[])

{
     int i=0;
     int joueurGagne = 1;
    for(i=0;i<tailleMot;i++)
      {

      if (lettreTrouvee[i] == 0)
        joueurGagne = 0;

      }
      return joueurGagne;
}

int main(int argc, char *argv[])
{
   int coups = 10,i=0;
   char secret[20];
   int *lettreTrouvee = NULL;
   char maLettre;
   int tailleMot = 0;

FILE *dico = fopen("dictionnaire.txt"," r" );

if (dico == NULL)
        exit(1);

rechercheMotSecret(dico,secret) ;

fclose(dico);

    tailleMot = strlen(secret) - 1;
    lettreTrouvee = malloc(tailleMot * sizeof(int));
    if (lettreTrouvee == NULL)
        exit(0);

    printf("Bienvenue dans le jeu du Pendu! ");

    for (i = 0; i<tailleMot;i++)
    {


        lettreTrouvee[i] = 0;
    }
    i = 0;
while (coups > 0 && !gagne(lettreTrouvee,tailleMot))
{
        printf("\n\nIl vous reste %d coups\nMot secret: ",coups);

        for(i=0;i<tailleMot;i++)
            if (lettreTrouvee[i] == 1)
        {
            printf("%c",secret[i]);
        }

        else
        {
            printf("*");
        }

    printf("\nProposer une lettre. ");

   maLettre = lireCaractere();

    if (!rechercheLettre(maLettre,lettreTrouvee,secret))
    {
        coups--;
    }


}

if (gagne(lettreTrouvee,tailleMot))

{
    free(lettreTrouvee);
    printf("\n\n BRAVO tu a GAGNE ! le mot secret etait bien %s",secret);
}
else
    printf("\n\nQuel nul alors tu a PERDU ! le mot secret etait %s",secret);


    return 0;

}





