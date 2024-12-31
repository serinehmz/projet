#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour repr�senter une commande
typedef struct {
    int numero_commande;
    char client[50];
    char date[20];
    char statut[20];
    float total;
} Commande;

// Variables globales pour le tableau dynamique
Commande *commandes = NULL;   // Pointeur vers le tableau des commandes
int taille_commandes = 0;     // Nombre actuel de commandes
int capacite = 0;             // Capacit� actuelle du tableau

// Initialisation du tableau dynamique avec une capacit� donn�e
void initialiser_tableau(int capacite_initiale) {
    capacite = capacite_initiale;
    commandes = (Commande *)malloc(capacite * sizeof(Commande));
    if (commandes == NULL) {
        printf("Erreur d'allocation m�moire.\n");
        exit(1);
    }
}

// Ajouter une commande au tableau dynamique
void ajouter_commande(Commande nouvelle_commande) {
    // Si le tableau est plein, doubler sa capacit�
    if (taille_commandes >= capacite) {
        capacite *= 2;
        Commande *temp = realloc(commandes, capacite * sizeof(Commande));
        if (temp == NULL) {
            printf("Erreur de r�allocation m�moire.\n");
            free(commandes);
            exit(1);
        }
        commandes = temp;
    }
    // Ajouter la nouvelle commande dans le tableau
    commandes[taille_commandes] = nouvelle_commande;
    taille_commandes++;
}

// Afficher l'historique des commandes
void afficher_historique() {
    int i;
	if (taille_commandes == 0) {
        printf("\nL'historique des commandes est vide.\n\n");
        return;
    }

    printf("\nHistorique des commandes :\n");
    printf("No\tClient\t\tDate\t\tStatut\t\tTotal\n");
    printf("-------------------------------------------------------------\n");

    for ( i = 0; i < taille_commandes; i++) {
        printf("%d\t%s\t%s\t%s\t%.2f\n",
               commandes[i].numero_commande,
               commandes[i].client,
               commandes[i].date,
               commandes[i].statut,
               commandes[i].total);
    }
    printf("\n");
}

// Rechercher une commande par son num�ro
Commande* rechercher_commande(int numero) {
	int i;
    for ( i = 0; i < taille_commandes; i++) {
        if (commandes[i].numero_commande == numero) {
            return &commandes[i];
        }
    }
    return NULL;
}

// Lib�rer la m�moire allou�e pour le tableau dynamique
void liberer_tableau() {
    free(commandes);
    commandes = NULL;
    capacite = 0;
    taille_commandes = 0;
}

// Fonction principale
int main() {
    // Initialiser le tableau dynamique avec une capacit� initiale
    initialiser_tableau(2);

    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Ajouter une commande\n");
        printf("2. Afficher l'historique des commandes\n");
        printf("3. Rechercher une commande\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Commande nouvelle_commande;
                printf("Entrez le num�ro de commande : ");
                scanf("%d", &nouvelle_commande.numero_commande);
                printf("Entrez le nom du client : ");
                scanf("%s", nouvelle_commande.client);
                printf("Entrez la date (AAAA-MM-JJ) : ");
                scanf("%s", nouvelle_commande.date);
                printf("Entrez le statut : ");
                scanf("%s", nouvelle_commande.statut);
                printf("Entrez le total : ");
                scanf("%f", &nouvelle_commande.total);

                ajouter_commande(nouvelle_commande);
                printf("Commande ajout�e avec succ�s.\n");
                break;
            }
            case 2:
                afficher_historique();
                break;
            case 3: {
                int numero;
                printf("Entrez le num�ro de commande � rechercher : ");
                scanf("%d", &numero);

                Commande *resultat = rechercher_commande(numero);
                if (resultat != NULL) {
                    printf("\nCommande trouv�e :\n");
                    printf("No : %d\nClient : %s\nDate : %s\nStatut : %s\nTotal : %.2f\n",
                           resultat->numero_commande,
                           resultat->client,
                           resultat->date,
                           resultat->statut,
                           resultat->total);
                } else {
                    printf("\nCommande non trouv�e.\n");
                }
                break;
            }
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choix != 4);

    // Lib�rer la m�moire avant de quitter
    liberer_tableau();

    return 0;
}

