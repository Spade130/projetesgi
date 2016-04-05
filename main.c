#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LIMITE 100

//fonction d'affichage du menu avec récuperation du choix de l'action: chiffrage ou dechiffrage
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
//fonction de chiffrage où l'on indique: fichier source analysé + fichier de destination pour le texte chiffré + clé de chiffrement
void Chiffrage(FILE *texteSource, FILE *texteDest, char key[], int l)
{
    char chaineAlpha[26] = "abcdefghijklmnopqrstuvwxyz";
    char caractere = 0;
    int i = 0;//compteur chaine alphabétique
    int j = 0;//compteur clé de chiffrage
    int z = 0;//variable qui contiendra la position de la lettre de la clé dans l'alphabet
    int y = 0;//variable qui contiendra la position de la lettre chiffrée
    int x = 0;//variable qui contiendra la position de la lettre claire

    do
    {
        //recuperation d'un caractère du texte source passé en minuscule pour analyse
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);

        //réinitialisation du compteur i à 0 dans la boucle do
        i = 0;

        //vérification: si l'on est arrivé à la fin du mot de la clé de chiffrage, retour au début sinon on conserve le compteur actuel
        if (j == l)
        {
            j = 0;
        }
        else
        {
            j = j;
        }

        //récupération de la position de la lettre de la clé dans l'alphabet
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

        i = 0; //retour compteur de la chaine alpha à 0

        //récupération de la position de la lettre claire dans l'alphabet  + celle de la lettre chiffrée
        do
        {
            if (caractere == chaineAlpha[i])
            {
                x = i;//position lettre claire

                //récupération de la position de la lettre chiffrée
                if ( (x + z) > 25) //cas particulier lorsque l'addition est plus grande que 25
                {
                    y = x + z;
                    y = y % 26;
                }
                else
                {
                    y = x + z;
                }
                //écriture de la lettre chiffrée dans le fichier chiffré
                fputc(chaineAlpha[y], texteDest);
                i = 26;//pour sortir de la boucle
                j++;//augmentation du compteur de la clé de chiffrage pour la prochaine lettre à analyser
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest);//cas particulier pour les caractères spéciaux qui sont recopiés tel quel
                i = 26;
                }
                else
                {
                    i++;//augmentation compteur chaine alphabétique pour continuer la comparaison si pas de correspondance avant
                }
            }
        }while(i <= 25);
    }while (caractere != EOF);//EOF identifie la fin du fichier analysé
}
//fonction de dechiffrage où l'on indique: fichier source analysé + fichier de destination pour le texte clair + clé de chiffrement
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
        //recuperation d'un caractère du texte source passé en minuscule pour analyse
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);

        //réinitialisation du compteur i à 0 dans la boucle do
        i = 0;

        //vérification: si l'on est arrivé à la fin du mot de la clé de chiffrage, retour au début sinon on conserve le compteur actuel
        if (j == l)
        {
            j = 0;
        }
        else
        {
            j = j;
        }

        //récupération de la position de la lettre de la clé dans l'alphabet
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

        i = 0;//retour compteur de la chaine alpha à 0

        //récupération de la position de la lettre chiffrée dans l'alphabet  + celle de la lettre claire
        do
        {
            if (caractere == chaineAlpha[i])
            {
                y = i;//position lettre chiffrée

                //récupération de la position de la lettre claire
                if ((y - z) < 0) //cas particulier lorsque la soustraction est inférieure à 0
                {
                    x = y - z;

                    x = 26 + x;
                }
                else
                {
                    x = y - z;
                }
                //écriture de la lettre claire dans le fichier clair
                fputc(chaineAlpha[x], texteDest);
                i = 26;//pour sortir de la boucle
                j++;//augmentation du compteur de la clé de chiffrage pour la prochaine lettre à analyser
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest);//cas particulier pour les caractères spéciaux qui sont recopiés tel quel
                i++;
                }
                else
                {
                    i++;//augmentation compteur chaine alphabétique pour continuer la comparaison si pas de correspondance avant
                }
            }
        }while(i <= 25);
    }while (caractere != EOF);//EOF identifie la fin du fichier analysé
}

int main()
{
    FILE* texteClair = NULL;//pour ouvrir le fichier contenant le message clair
    FILE* texteChiff = NULL;//pour ouvrir le fichier contenant le message chiffré
    FILE* texteKey = NULL;//pour ouvrir le fichier contenant la clé de chiffrage
    char key[LIMITE]="";//chaine de caractere avec une taille limite Constante définie en début de code: ici 100 Max
    int l = 0;//va récupérer la longueur de la clé de chiffrage

    //récupération de la clé de chiffrage
    texteKey = fopen("key.txt", "r");
    fgets(key, LIMITE, texteKey);
    fclose(texteKey);

    //récupération de la taille de la clé
    l = strlen(key);

    switch(Menu())
    {
        case 1:
            //ouverture des fichiers: pour le chiffrage message claire en lecture et message chiffré en écriture (avec suppression du contenu précédent)
            texteClair = fopen("lettre.txt", "r");
            texteChiff = fopen("lettreChiffre.txt", "w+");

            if (texteClair != NULL && texteChiff != NULL)//test bonne ouverture des fichiers avant action
            {
                //appel de ma fonction en précisant: fichier source + fichier destination + clé de chiffrage + taille de la clé de chiffrage
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
                //appel de ma fonction en précisant: fichier source + fichier destination + clé de chiffrage + taille de la clé de chiffrage
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
