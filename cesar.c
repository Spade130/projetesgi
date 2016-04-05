#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//fonction d'affichage du menu avec recuperation du choix de l'action: chiffrage ou dechiffrage
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
//fonction de chiffrage et dechiffrage, la clé est fixée à 3 lors du chiffrement et à -3 lors du dechiffrement (à l'appel de la fonction dans le main
void Chiffrage(FILE *texteSource, FILE *texteDest, signed key)
{
    char chaineAlpha[26] = "abcdefghijklmnopqrstuvwxyz"; //chaine de comparaison pour identifier les lettres du texte
    char caractere = 0;
    int i = 0;

    do
    {
        //recuperation d'un caractere du texte passé en minuscule pour analyse / la boucle permet d'analyser tous les caractères du texte
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);
        i = 0;
        do
        {
            //identification de la lettre à chiffrer ou dechiffrer
            if (caractere == chaineAlpha[i])
            {
                if (i + key > 25)
                {
                    i = (i + key) % 26; //cas particulier pour le chiffrement / le reste de la division indique la position dans l'alphabet
                }
                else if ( i + key < 0)
                {
                    i = i + key + 26; //cas particulier pour le dechiffrement
                }
                else
                {
                    i = i + key;
                }
            //ecriture de la lettre chiffrée dans un deuxième fichier: lettre chiffrée pour le chiffrement / lettre Claire pour le dechiffrement
            fputc(chaineAlpha[i], texteDest);
            i = 26;
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest); //cas particulier des caractères spéciaux (ou espaces): je les recopie tel quel
                i++;
                }
                else
                {
                    i = i + 1;
                }
            }
        }while(i <= 25);
    }while (caractere != EOF); //EOF indique la fin du fichier
}

int main()
{
    FILE* texteClair = NULL; //fichier qui contient le message Clair
    FILE* texteChiff = NULL;//fichier qui contient le message chiffré
    signed key = 3;//clé de chiffrement imposée à 3

    switch(Menu())
    {
        case 1:
            //ouverture des fichiers: pour le chiffrage message claire en lecture et message chiffré en écriture
            texteClair = fopen("lettre.txt", "r");
            texteChiff = fopen("lettreChiffre.txt", "w+");

            if (texteClair != NULL && texteChiff != NULL)
            {
                //appel de ma fonction en précisant quel est mon fichier source et mon fichier destination + la clé imposée à 3 ici
                Chiffrage(texteClair, texteChiff, key);
                printf("Le chiffrage est effectif!\n");
            }
            else
            {
                printf("Impossible d'ouvrir le fichier");
            }
            break;
        case 2:
            texteClair = fopen("lettre.txt", "w+");
            texteChiff = fopen("lettreChiffre.txt", "r");

            if (texteClair != NULL && texteChiff != NULL)
            {
                //clé convertie en negatif car l'on veut déchiffrer, déplacement contraire dans l'alphabet
                key = -key;
                //ouverture des fichiers: pour le chiffrage message claire en lecture et message chiffré en écriture
                Chiffrage(texteChiff, texteClair, key);
                printf("Le chiffrage est effectif!\n");
            }
            else
            {
                printf("Impossible d'ouvrir le fichier"); //pour avoir un retour en cas de problème d'ouverture de fichier
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
