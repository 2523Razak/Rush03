# Rush03

# Système de Gestion d'Étudiants en C

**Auteur** : Razak Boureima Issa Adamou  
**Public visé** : Débutants en programmation C

## Introduction

Ce programme permet de gérer une liste d'étudiants avec leurs notes. Il montre comment :
- Utiliser les structures (`struct`)
- Manipuler les fichiers
- Créer des menus interactifs
- Valider les entrées utilisateur

## Comment ça marche ?

### 1. La Structure Étudiant
```c
typedef struct {
    char nom[50];    // Stocke le nom (49 caractères max + '\0')
    char prenom[50]; // Stocke le prénom
    int id;          // Numéro unique
    float note;      // Note entre 0 et 20
} Etudiant;
```
*Exemple* :  
Pour "Razak Boureima", ID 01, note 15.5, la structure contient :
- nom = "Razak"
- prenom = "Boureima"
- id = 01
- note = 15.5

### 2. Stockage des Données
```c
Etudiant etudiants[MAX_ETUDIANTS]; // Tableau de 100 étudiants max
int nb_etudiants = 0;              // Compteur actuel
```

### 3. Fonctionnement du Programme
1. Au démarrage : charge les données depuis `etudiants.txt`
2. Affiche un menu avec 6 options
3. Exécute l'action choisie
4. Répète jusqu'à ce qu'on choisisse "Quitter"

## Explications des Parties Importantes

### 1. Ajout d'un Étudiant (`ajouter_etudiant()`)
1. Vérifie qu'il reste de la place
2. Demande chaque information :
   ```c
   printf("Note : ");
   while(scanf("%f", &e.note) != 1 || e.note < 0 || e.note > 20) {
       printf("Note invalide (0-20). Recommencez : ");
       while(getchar() != '\n');
   }
   ```
   *Pourquoi* : Garantit que la note est un nombre entre 0 et 20

3. Ajoute au tableau et incrémente le compteur

### 2. Affichage Formaté (`afficher_etudiant()`)
```c
printf("| ID : %-29d |\n", e.id);
```
Le `%-29d` signifie :
- `-` : Alignement à gauche
- `29` : Largeur fixe de 29 caractères
- `d` : Nombre entier

### 3. Tri par Notes (`afficher_etudiants_tries_notes()`)
Méthode utilisée : **Tri par sélection**
1. Crée une copie du tableau
2. Trouve l'étudiant avec la meilleure note
3. Le place en première position
4. Répète pour les positions suivantes

*Exemple* :  
Avant : [12, 15, 10]  
Après : [15, 12, 10]

## Gestion des Fichiers

### Sauvegarde (`sauvegarder_donnees()`)
Écrit dans `etudiants.txt` avec le format :
```
Nom
Prénom
ID
Note
```
*Exemple* :
```
Razak
Boureima
01
15.50
```

### Chargement (`charger_donnees()`)
Lit le fichier ligne par ligne et remplit le tableau :
```c
while(fgets(etudiants[nb_etudiants].nom, 50, f) != NULL) {
    // Supprime le \n
    etudiants[nb_etudiants].nom[strcspn(..., "\n")] = '\0';
    // Lit les autres champs...
    nb_etudiants++;
}
```

## Comment Utiliser le Programme ?

### Compilation
```bash
gcc gestion_scolaire.c -o gestion
```

### Exécution
```bash
./gestion
```

### Dans Termux (Android)
```bash
clang gestion_scolaire.c -o gestion
./gestion
```

## Exemple Complet d'Utilisation

1. Ajouter 2 étudiants :
   ```
   Nom : Razak
   Prénom : Boureima
   ID : 01
   Note : 15.5

   Nom : Ali
   Prénom : Moussa
   ID : 02
   Note : 16.5
   ```

2. Lister les étudiants :
   ```
   ___________________________________
   | ID : 101                        |
   | Nom : Razak                    |
   | Prenom : Boureima                   |
   | Note : 15.5                     |
   |___________________________________|
   ```

3. Trier par notes :
   ```
   (Affiche Ali d'abord car 16.5 > 15.5)
   ```

4. Sauvegarder et quitter

## Questions

**Q** : Pourquoi utiliser `strcspn()` ?  
**R** : Pour supprimer le `\n` que `fgets()` garde à la fin des chaînes.

**Q** : Comment augmenter la capacité au-delà de 100 étudiants ?  
**R** : Modifiez la valeur de `MAX_ETUDIANTS`.

**Q** : Où sont stockées les données ?  
**R** : Dans `etudiants.txt` dans le même dossier.
