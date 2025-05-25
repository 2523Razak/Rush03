#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ETUDIANTS 100
#define FICHIER_DONNEES "etudiants.txt"

typedef struct {
    char nom[50];
    char prenom[50];
    int id;
    float note;
} Etudiant;

Etudiant etudiants[MAX_ETUDIANTS];
int nb_etudiants = 0;
int modifications_non_sauvegardees = 0;

/* Prototypes des fonctions */
void effacer_ecran();
void afficher_menu();
void ajouter_etudiant();
void afficher_etudiants();
void afficher_etudiants_tries_notes();
void supprimer_etudiant();
void sauvegarder_donnees();
void charger_donnees();
void quitter();

int main() {
    charger_donnees();
    
    int choix;
    do {
        effacer_ecran();
        afficher_menu();
        printf("\nVotre choix : ");
        
        if(scanf("%d", &choix) != 1) {
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        
        switch(choix) {
            case 1: ajouter_etudiant(); break;
            case 2: afficher_etudiants(); break;
            case 3: afficher_etudiants_tries_notes(); break;
            case 4: supprimer_etudiant(); break;
            case 5: sauvegarder_donnees(); break;
            case 6: quitter(); break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while(1);
    
    return 0;
}

void effacer_ecran() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void afficher_menu() {
    printf("\n=== GESTION SCOLAIRE ===\n");
    printf("1. Ajouter un etudiant\n");
    printf("2. Lister les etudiants\n");
    printf("3. Lister par notes (decroissant)\n");
    printf("4. Supprimer un etudiant\n");
    printf("5. Sauvegarder les donnees\n");
    printf("6. Quitter le programme\n");
}

void ajouter_etudiant() {
    effacer_ecran();
    if(nb_etudiants >= MAX_ETUDIANTS) {
        printf("Capacite maximale atteinte (%d etudiants)!\n", MAX_ETUDIANTS);
        printf("Appuyez sur Entree pour continuer...");
        while(getchar() != '\n');
        return;
    }
    
    Etudiant e;
    
    printf("\n--- NOUVEL ETUDIANT ---\n");
    
    printf("Nom : ");
    fgets(e.nom, 50, stdin);
    e.nom[strcspn(e.nom, "\n")] = '\0';
    
    printf("Prenom : ");
    fgets(e.prenom, 50, stdin);
    e.prenom[strcspn(e.prenom, "\n")] = '\0';
    
    printf("ID : ");
    while(scanf("%d", &e.id) != 1) {
        printf("ID invalide. Recommencez : ");
        while(getchar() != '\n');
    }
    
    printf("Note : ");
    while(scanf("%f", &e.note) != 1 || e.note < 0 || e.note > 20) {
        printf("Note invalide (0-20). Recommencez : ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    
    etudiants[nb_etudiants++] = e;
    modifications_non_sauvegardees++;
    
    printf("\nEtudiant ajoute avec succes!\n");
    printf("Appuyez sur Entree pour continuer...");
    while(getchar() != '\n');
}

void afficher_etudiant(Etudiant e) {
    printf("___________________________________\n");
    printf("| ID : %-29d|\n", e.id);
    printf("| Nom : %-27s |\n", e.nom);
    printf("| Prenom : %-24s |\n", e.prenom);
    printf("| Note : %-27.1f|\n", e.note);
    printf("|___________________________________|\n");
}

void afficher_etudiants() {
    effacer_ecran();
    if(nb_etudiants == 0) {
        printf("\nAucun etudiant enregistre.\n");
    } else {
        printf("\n=== LISTE DES ETUDIANTS ===\n");
        printf("Total: %d etudiant(s)\n\n", nb_etudiants);
        
        for(int i = 0; i < nb_etudiants; i++) {
            afficher_etudiant(etudiants[i]);
        }
    }
    
    printf("\n1. Retour au menu\n");
    printf("2. Quitter\n");
    printf("Choix : ");
    
    int choix;
    while(scanf("%d", &choix) != 1 || (choix != 1 && choix != 2)) {
        printf("Choix invalide. Entrez 1 ou 2 : ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    
    if(choix == 2) quitter();
}

void afficher_etudiants_tries_notes() {
    effacer_ecran();
    if(nb_etudiants == 0) {
        printf("\nAucun etudiant enregistre.\n");
        printf("Appuyez sur Entree pour continuer...");
        while(getchar() != '\n');
        return;
    }
    
    // Créer une copie pour trier sans modifier l'original
    Etudiant copie[MAX_ETUDIANTS];
    memcpy(copie, etudiants, sizeof(Etudiant) * nb_etudiants);
    
    // Tri par sélection décroissant
    for(int i = 0; i < nb_etudiants-1; i++) {
        int max_idx = i;
        for(int j = i+1; j < nb_etudiants; j++) {
            if(copie[j].note > copie[max_idx].note) {
                max_idx = j;
            }
        }
        if(max_idx != i) {
            Etudiant temp = copie[i];
            copie[i] = copie[max_idx];
            copie[max_idx] = temp;
        }
    }
    
    printf("\n=== CLASSEMENT PAR NOTES ===\n");
    printf("(Du meilleur au moins bon)\n\n");
    
    for(int i = 0; i < nb_etudiants; i++) {
        afficher_etudiant(copie[i]);
    }
    
    printf("\n1. Retour au menu\n");
    printf("2. Quitter\n");
    printf("Choix : ");
    
    int choix;
    while(scanf("%d", &choix) != 1 || (choix != 1 && choix != 2)) {
        printf("Choix invalide. Entrez 1 ou 2 : ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    
    if(choix == 2) quitter();
}

void supprimer_etudiant() {
    effacer_ecran();
    if(nb_etudiants == 0) {
        printf("\nAucun etudiant a supprimer.\n");
        printf("Appuyez sur Entree pour continuer...");
        while(getchar() != '\n');
        return;
    }
    
    printf("\n=== SUPPRIMER UN ETUDIANT ===\n");
    printf("Liste des ID disponibles : ");
    for(int i = 0; i < nb_etudiants; i++) {
        printf("%d", etudiants[i].id);
        if(i < nb_etudiants-1) printf(", ");
    }
    printf("\n\nEntrez l'ID de l'etudiant a supprimer : ");
    
    int id;
    while(scanf("%d", &id) != 1) {
        printf("ID invalide. Recommencez : ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');
    
    int trouve = 0;
    for(int i = 0; i < nb_etudiants; i++) {
        if(etudiants[i].id == id) {
            // Décalage des éléments suivants
            for(int j = i; j < nb_etudiants-1; j++) {
                etudiants[j] = etudiants[j+1];
            }
            nb_etudiants--;
            modifications_non_sauvegardees++;
            trouve = 1;
            break;
        }
    }
    
    if(trouve) {
        printf("\nEtudiant avec ID %d supprime avec succes!\n", id);
    } else {
        printf("\nAucun etudiant trouve avec l'ID %d\n", id);
    }
    
    printf("Appuyez sur Entree pour continuer...");
    while(getchar() != '\n');
}

void sauvegarder_donnees() {
    effacer_ecran();
    FILE *f = fopen(FICHIER_DONNEES, "w");
    if(f == NULL) {
        printf("Erreur: impossible de creer le fichier!\n");
        printf("Appuyez sur Entree pour continuer...");
        while(getchar() != '\n');
        return;
    }
    
    for(int i = 0; i < nb_etudiants; i++) {
        fprintf(f, "%s\n%s\n%d\n%.2f\n", 
                etudiants[i].nom,
                etudiants[i].prenom,
                etudiants[i].id,
                etudiants[i].note);
    }
    
    fclose(f);
    modifications_non_sauvegardees = 0;
    printf("\nDonnees sauvegardees avec succes!\n");
    printf("%d etudiants enregistres.\n", nb_etudiants);
    printf("Appuyez sur Entree pour continuer...");
    while(getchar() != '\n');
}

void charger_donnees() {
    FILE *f = fopen(FICHIER_DONNEES, "r");
    if(f == NULL) return;
    
    char buffer[100];
    nb_etudiants = 0;
    
    while(nb_etudiants < MAX_ETUDIANTS && fgets(etudiants[nb_etudiants].nom, 50, f) != NULL) {
        etudiants[nb_etudiants].nom[strcspn(etudiants[nb_etudiants].nom, "\n")] = '\0';
        
        if(fgets(etudiants[nb_etudiants].prenom, 50, f) == NULL) break;
        etudiants[nb_etudiants].prenom[strcspn(etudiants[nb_etudiants].prenom, "\n")] = '\0';
        
        if(fgets(buffer, 100, f) == NULL) break;
        etudiants[nb_etudiants].id = atoi(buffer);
        
        if(fgets(buffer, 100, f) == NULL) break;
        etudiants[nb_etudiants].note = atof(buffer);
        
        nb_etudiants++;
    }
    
    fclose(f);
}

void quitter() {
    effacer_ecran();
    if(modifications_non_sauvegardees > 0) {
        char reponse;
        printf("Voulez-vous sauvegarder les modifications avant de quitter? (o/n) ");
        scanf(" %c", &reponse);
        
        if(tolower(reponse) == 'o') {
            sauvegarder_donnees();
        }
        while(getchar() != '\n');
    }
    
    printf("\nMerci d'avoir utilise notre systeme!\n");
    exit(0);
}
