#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure du Maillon
typedef struct m
{
    int n;
    char nom[100];
    struct m *next;

} Maillon;

// Initialisation d'un maillon
Maillon *initMaillon(int n, const char *nom)
{
    // allocation mémoire
    Maillon *temp = malloc(sizeof(Maillon));

    // Initialisation
    strcpy(temp->nom, nom);
    temp->n = n;
    temp->next = NULL;

    // Renvoie l'adresse allouée.
    return temp;
}

// Ajout fin récursif
void ajoutFinRecur(Maillon **pointeurSurListe, int n, const char *nom)
{
    // On récupère la liste
    Maillon *liste = *pointeurSurListe;

    if(liste == NULL){
        liste = initMaillon(n,nom);
    }else{
        ajoutFinRecur(&(liste->next), n, nom);
    }

    // on n'oublie pas de recoller la liste au pointeur
    *pointeurSurListe = liste;
}


// liberation de la liste avec while
void libererListe(Maillon **pointeurSurListe)
{
    Maillon *liste = *pointeurSurListe;
    Maillon *temp = NULL;

    while (liste != NULL)
    {
        temp = liste->next;
        free(liste);
        liste = temp;
    }

    *pointeurSurListe = NULL;
}

void afficherListeAvecWhile(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("Liste vide \n");
    }
    else
    {
        printf("HEAD \n");
        while (liste != NULL)
        {
            printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
            liste = liste->next;
        }
        printf("TAIL \n");
    }
}

void afficherListeAvecFor(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("Liste vide \n");
    }
    else
    {
        for (; liste != NULL; liste = liste->next)
        {
            printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
        }
    }
}

void afficherListeRecur(Maillon *liste)
{

    if (liste == NULL)
    {
        printf("TAIL\n");
    }
    else
    {
        printf("Nom : %s, Maillon: %d \n", liste->nom, liste->n);
        afficherListeRecur(liste->next);
    }
}

void freeRec(Maillon **m){

    if(*m == NULL)
        return;
    freeRec(&((*m)->next));
    free(*m);
    *m= NULL;

}

void procAjoutEnTeteDeListe(Maillon **m, int n, const char *nom)
{
    // Creation d'un maillon dans la memoire
    Maillon *temp = initMaillon(n,nom);

    if(*m == NULL){
        *m = temp;
    }else{
        temp->next =  *m; // ancienne tete
        *m = temp;
    }
}

void procAjoutEnFinDeListe(Maillon **m, int n, const char *nom)
{
    Maillon *temp = initMaillon(n, nom);
    Maillon *tail = *m;

    if (*m == NULL)
    {
        *m = temp;
    }
    else
    {
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = temp;
    }

}



int main()
{
    printf("\n\n********* Liste simplement chaînée *********\n\n");
    Maillon *liste = NULL;

    // Ajout (recursive) en fin de liste (TAIL)
    ajoutFinRecur(&liste, 1, "A");
    ajoutFinRecur(&liste, 2, "B");

    // Test des methodes d'affichage
    printf("\n\n********* Affiche while *********\n\n");
    afficherListeAvecWhile(liste);

    printf("\n\n********* Affiche recur *********\n\n");
    printf("HEAD \n");
    afficherListeRecur(liste);

    printf("\n\n********* Ajouter en tete*******\n\n");
    procAjoutEnTeteDeListe(&liste,3,"C");
    procAjoutEnTeteDeListe(&liste,4,"D");
    afficherListeAvecWhile(liste);

    printf("\n\n********* Ajouter en fin *******\n\n");
    procAjoutEnFinDeListe(&liste,5,"E");
    procAjoutEnFinDeListe(&liste,6,"F");
    afficherListeAvecWhile(liste);


    // Liberation
    printf("\n\n********* Free ******************\n\n");
    libererListe(&liste);
    afficherListeAvecWhile(liste);

}