#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LIMITE 100

//fonction d'affichage du menu avec r�cuperation du choix de l'action: chiffrage ou dechiffrage
int Menu()
{
    int choix = 0;
    while (choix != 1 && choix !=2)
    {
        printf("Programme de chiffrage/dechiffrage:\n\nMenu\n1: Chiffrer un texte\n2: Dechiffrer un texte\n\nchoix:");
        scanf("%d", &choix);
     }
     return choix;
}
//fonction de chiffrage o� l'on indique: fichier source analys� + fichier de destination pour le texte chiffr� + cl� de chiffrement
void Chiffrage(FILE *texteSource, FILE *texteDest, char key[], int l)
{
    char chaineAlpha[26] = "abcdefghijklmnopqrstuvwxyz";
    char caractere = 0;
    int i = 0;//compteur chaine alphab�tique
    int j = 0;//compteur cl� de chiffrage
    int z = 0;//variable qui contiendra la position de la lettre de la cl� dans l'alphabet
    int y = 0;//variable qui contiendra la position de la lettre chiffr�e
    int x = 0;//variable qui contiendra la position de la lettre claire

    do
    {
        //recuperation d'un caract�re du texte source pass� en minuscule pour analyse
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);

        //r�initialisation du compteur i � 0 dans la boucle do
        i = 0;

        //v�rification: si l'on est arriv� � la fin du mot de la cl� de chiffrage, retour au d�but sinon on conserve le compteur actuel
        if (j == l)
        {
            j = 0;
        }
        else
        {
            j = j;
        }

        //r�cup�ration de la position de la lettre de la cl� dans l'alphabet
        do
        {
            if (key[j] == chaineAlpha[i])
            {
                z = i;
                i = 26;
            }
            else
            {
                i++;
            }
        }while (i <= 25);

        i = 0; //retour compteur de la chaine alpha � 0

        //r�cup�ration de la position de la lettre claire dans l'alphabet  + celle de la lettre chiffr�e
        do
        {
            if (caractere == chaineAlpha[i])
            {
                x = i;//position lettre claire

                //r�cup�ration de la position de la lettre chiffr�e
                if ( (x + z) > 25) //cas particulier lorsque l'addition est plus grande que 25
                {
                    y = x + z;
                    y = y % 26;
                }
                else
                {
                    y = x + z;
                }
                //�criture de la lettre chiffr�e dans le fichier chiffr�
                fputc(chaineAlpha[y], texteDest);
                i = 26;//pour sortir de la boucle
                j++;//augmentation du compteur de la cl� de chiffrage pour la prochaine lettre � analyser
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest);//cas particulier pour les caract�res sp�ciaux qui sont recopi�s tel quel
                i = 26;
                }
                else
                {
                    i++;//augmentation compteur chaine alphab�tique pour continuer la comparaison si pas de correspondance avant
                }
            }
        }while(i <= 25);
    }while (caractere != EOF);//EOF identifie la fin du fichier analys�
}
//fonction de dechiffrage o� l'on indique: fichier source analys� + fichier de destination pour le texte clair + cl� de chiffrement
void DeChiffrage(FILE *texteSource, FILE *texteDest, char key[], int l)
{
    char chaineAlpha[26] = "abcdefghijklmnopqrstuvwxyz";
    char caractere = 0;
    int i = 0;
    int j = 0;
    int z = 0;
    int y = 0;
    signed x = 0;

    do
    {
        //recuperation d'un caract�re du texte source pass� en minuscule pour analyse
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);

        //r�initialisation du compteur i � 0 dans la boucle do
        i = 0;

        //v�rification: si l'on est arriv� � la fin du mot de la cl� de chiffrage, retour au d�but sinon on conserve le compteur actuel
        if (j == l)
        {
            j = 0;
        }
        else
        {
            j = j;
        }

        //r�cup�ration de la position de la lettre de la cl� dans l'alphabet
        do
        {
            if (key[j] == chaineAlpha[i])
            {
                z = i;
                i = 26;
            }
            else
            {
                i++;
            }
        }while (i <= 25);

        i = 0;//retour compteur de la chaine alpha � 0

        //r�cup�ration de la position de la lettre chiffr�e dans l'alphabet  + celle de la lettre claire
        do
        {
            if (caractere == chaineAlpha[i])
            {
                y = i;//position lettre chiffr�e

                //r�cup�ration de la position de la lettre claire
                if ((y - z) < 0) //cas particulier lorsque la soustraction est inf�rieure � 0
                {
                    x = y - z;

                    x = 26 + x;
                }
                else
                {
                    x = y - z;
                }
                //�criture de la lettre claire dans le fichier clair
                fputc(chaineAlpha[x], texteDest);
                i = 26;//pour sortir de la boucle
                j++;//augmentation du compteur de la cl� de chiffrage pour la prochaine lettre � analyser
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest);//cas particulier pour les caract�res sp�ciaux qui sont recopi�s tel quel
                i++;
                }
                else
                {
                    i++;//augmentation compteur chaine alphab�tique pour continuer la comparaison si pas de correspondance avant
                }
            }
        }while(i <= 25);
    }while (caractere != EOF);//EOF identifie la fin du fichier analys�
}

int main()
{
    FILE* texteClair = NULL;//pour ouvrir le fichier contenant le message clair
    FILE* texteChiff = NULL;//pour ouvrir le fichier contenant le message chiffr�
    FILE* texteKey = NULL;//pour ouvrir le fichier contenant la cl� de chiffrage
    char key[LIMITE]="";//chaine de caractere avec une taille limite Constante d�finie en d�but de code: ici 100 Max
    int l = 0;//va r�cup�rer la longueur de la cl� de chiffrage

    //r�cup�ration de la cl� de chiffrage
    texteKey = fopen("key.txt", "r");
    fgets(key, LIMITE, texteKey);
    fclose(texteKey);

    //r�cup�ration de la taille de la cl�
    l = strlen(key);

    switch(Menu())
    {
        case 1:
            //ouverture des fichiers: pour le chiffrage message claire en lecture et message chiffr� en �criture (avec suppression du contenu pr�c�dent)
            texteClair = fopen("lettre.txt", "r");
            texteChiff = fopen("lettreChiffre.txt", "w+");

            if (texteClair != NULL && texteChiff != NULL)//test bonne ouverture des fichiers avant action
            {
                //appel de ma fonction en pr�cisant: fichier source + fichier destination + cl� de chiffrage + taille de la cl� de chiffrage
                Chiffrage(texteClair, texteChiff, key, l);
                printf("Le chiffrage est effectif!\n");
            }
            else
            {
                printf("Impossible d'ouvrir le fichier, desole!");
            }
            break;
        case 2:


            texteClair = fopen("lettre.txt", "w+");
            texteChiff = fopen("lettreChiffre.txt", "r");

            if (texteClair != NULL && texteChiff != NULL)
            {
                //appel de ma fonction en pr�cisant: fichier source + fichier destination + cl� de chiffrage + taille de la cl� de chiffrage
                DeChiffrage(texteChiff, texteClair, key, l);
                printf("Le dechiffrage est effectif!\n");
            }
            else
            {
                printf("Impossible d'ouvrir le fichier");
            }
            break;
        default:
            printf("Le choix effectue n'est pas valide, taper 1 pour chiffrer ou 2 pour dechiffrer");
            break;
    }
    //fermeture des fichiers
    fclose(texteClair);
    fclose(texteChiff);

    system("pause");

    return (0);
}
