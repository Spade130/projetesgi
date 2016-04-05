#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
//fonction de r�cup�ration de la cl� de chiffrage
int Key()
{
    int key = 0;
    while (key < 1 || key > 25)//test sur la cl�, entier positif attendu
    {
        printf("\nQuelle clef voulez vous? Elle represente le decalage dans l'alphabet, elle doit �tre comprise entre 1 et 25\n");
        scanf("%d", &key);
    }
    return key;
}
//fonction de chiffrage et dechiffrage, on y indique le fichier source et destination et la cl� renseign�e avant
void Chiffrage(FILE *texteSource, FILE *texteDest, signed key)
{
    char chaineAlpha[26] = "abcdefghijklmnopqrstuvwxyz";
    char caractere = 0;
    int i = 0;

    do
    {
        //recuperation d'un caractere du texte pass� en minuscule pour analyse / la boucle permet d'analyser tous les caract�res du texte
        caractere = fgetc(texteSource);
        caractere = tolower(caractere);
        i = 0;
        do
        {
            //identification de la lettre � chiffrer ou dechiffrer
            if (caractere == chaineAlpha[i])
            {
                if (i + key > 25)
                {
                    i = (i + key) % 26;//cas particulier pour le chiffrement / le reste de la division indique la position dans l'alphabet
                }
                else if ( i + key < 0)
                {
                    i = i + key + 26;//cas particulier pour le dechiffrement
                }
                else
                {
                    i = i + key;
                }
            //ecriture de la lettre chiffr�e dans un deuxi�me fichier: (lettre chiffr�e pour le chiffrement / lettre Claire pour le dechiffrement)
            fputc(chaineAlpha[i], texteDest);
            i = 26;
            }
            else
            {
                if(i == 25)
                {
                fputc(caractere, texteDest);//cas particulier des caract�res sp�ciaux (ou espaces): je les recopie tel quel
                i++;
                }
                else
                {
                    i = i + 1;
                }
            }
        }while(i <= 25);
    }while (caractere != EOF);//EOF indique la fin du fichier
}

int main()
{
    signed key = 0;//cl� de chiffrement: variable qui va r�cuperer la cl� du user
    FILE* texteClair = NULL;//fichier qui contient le message Clair
    FILE* texteChiff = NULL;//fichier qui contient le message chiffr�

    switch(Menu())
    {
        case 1:
            //r�cup�ration de la cl� aupr�s de l'utilisateur
            key = Key();
            //ouverture des fichiers: pour le chiffrage message clair en lecture et message chiffr� en �criture (avec suppression du contenu pr�c�dent)
            texteClair = fopen("lettre.txt", "r");
            texteChiff = fopen("lettreChiffre.txt", "w+");

            if (texteClair != NULL && texteChiff != NULL)//test bonne ouverture des fichiers avant action
            {
                //appel de ma fonction en pr�cisant quel est mon fichier source et mon fichier destination + la cl� de chiffrage
                Chiffrage(texteClair, texteChiff, key);
                printf("Le chiffrage est effectif!\n");
            }
            else
            {
                printf("Impossible d'ouvrir le fichier, desole!");
            }
            break;
        case 2:
            key = Key();
            //cl� convertie en negatif car l'on veut d�chiffrer, d�placement contraire dans l'alphabet
            key = -key;
            //ouverture des fichiers: pour le chiffrage message chiffr� en lecture et message clair en �criture
            texteClair = fopen("lettre.txt", "w+");
            texteChiff = fopen("lettreChiffre.txt", "r");

            if (texteClair != NULL && texteChiff != NULL)
            {
                Chiffrage(texteChiff, texteClair, key);
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

