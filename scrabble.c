#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "scrabble.h"

caractere lettres[26] = {
    {'A', 9, 1}, {'B', 2, 3}, {'C', 2, 3}, {'D', 3, 2}, {'E', 15, 1}, 
    {'F', 2, 4}, {'G', 2, 2}, {'H', 2, 4}, {'I', 8, 1}, {'J', 1, 8}, 
    {'K', 1, 10}, {'L', 5, 1}, {'M', 3, 2}, {'N', 6, 1}, {'O', 6, 1}, 
    {'P', 2, 3}, {'Q', 1, 8}, {'R', 6, 1}, {'S', 6, 1}, {'T', 6, 1}, 
    {'U', 6, 1}, {'V', 2, 4}, {'W', 1, 10}, {'X', 1, 10}, {'Y', 1, 10}, 
    {'Z', 1, 10}
};

/*caractere lettres[26] = {
    {'A', 1, 1}, {'B', 1, 3}, {'C', 1, 3}, {'D', 1, 2}, {'E', 1, 1}, 
    {'F', 1, 4}, {'G', 1, 2}, {'H', 1, 4}, {'I', 1, 1}, {'J', 1, 8}, 
    {'K', 1, 10}, {'L', 1, 1}, {'M', 1, 2}, {'N', 1, 1}, {'O', 1, 1}, 
    {'P', 1, 3}, {'Q', 1, 8}, {'R', 1, 1}, {'S', 1, 1}, {'T', 1, 1}, 
    {'U', 1, 1}, {'V', 1, 4}, {'W', 1, 10}, {'X', 1, 10}, {'Y', 1, 10}, 
    {'Z', 1, 10}
};*/

caractere vide = {' ', 9, 1};

couple coordonnees_cases_mot_double[17] = {
    {1, 1}, {2, 2}, {3, 3}, {4, 4}, {13, 1}, {12, 2},
    {11, 3}, {10, 4}, {4, 10}, {3, 11}, {2, 12}, {1, 13},
    {10, 10}, {11, 11}, {12, 12}, {13, 13}, {7, 7}
};

couple coordonnees_cases_mot_triple[8] = {
    {0, 0}, {0, 7}, {0, 14}, {7, 0},
    {7, 14}, {14, 0}, {14, 7}, {14, 14}
};

couple coordonnees_cases_lettre_double[24] = {
    {3, 0}, {11, 0}, {6, 2}, {8, 2}, {0, 3}, {7, 3}, {14, 3}, {2, 6}, {6, 6}, {8, 6}, {12, 6}, {3, 7}, {11, 7}, {2, 8}, {6, 8}, {8, 8},
    {12, 8}, {0, 11}, {7, 11}, {14, 11}, {6, 12}, {8, 12}, {3, 14}, {11, 14}
};

couple coordonnees_cases_lettre_triple[12] = {
    {5, 1}, {9, 1}, {1, 5}, {5, 5}, {9, 5}, {13, 5}, {1, 9}, {5, 9}, {9, 9}, {13, 9}, {5, 13}, {9, 13}
};

const int TAILLE_PLATEAU = 15;
char* dic[500000];
caractere* sac;
int nb_pioche = 0;

Case **init_plateau() {
    Case **resultat = malloc(TAILLE_PLATEAU * sizeof(Case *));
    if (!resultat) {
        perror("Erreur d'allocation mémoire pour le plateau\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        resultat[i] = malloc(TAILLE_PLATEAU * sizeof(Case));
        if (!resultat[i]) {
            perror("Erreur d'allocation mémoire pour une ligne du plateau\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            resultat[i][j].type = N;  
            resultat[i][j].c = vide;
            resultat[i][j].est_placee = false;     
        }
    }

    return resultat;
}

void init_case_lettre_double_plateau(Case **plateau, couple coordonnees[]) {
    for (int i = 0; i < 24; i++){
        int x = coordonnees[i].x;
        int y = coordonnees[i].y;
        plateau[x][y].type = LD;
    }
}

void init_case_lettre_triple_plateau(Case **plateau, couple coordonnees[]) {
    for (int i = 0; i < 12; i++){
        int x = coordonnees[i].x;
        int y = coordonnees[i].y;
        plateau[x][y].type = LT;
    }
}

void init_case_mot_double_plateau(Case** plateau, couple coordonnees[]) {
    for (int i = 0; i < 17; i++) {
        int x = coordonnees[i].x;
        int y = coordonnees[i].y;
        plateau[x][y].type = MD;
    }
}

void init_case_mot_triple_plateau(Case** plateau, couple coordonnees[]) {
    for (int i = 0; i < 8; i++) {
        int x = coordonnees[i].x;
        int y = coordonnees[i].y;
        plateau[x][y].type = MT;
    }
}

void affiche_tab(Case **tab) {
    for (int j = 0; j < TAILLE_PLATEAU; j++) {
        // Ligne supérieure des cases
        for (int i = 0; i < TAILLE_PLATEAU; i++) {
            printf("+---");
        }
        printf("+\n");

        // Contenu des cases
        for (int i = 0; i < TAILLE_PLATEAU; i++) {
            char symbole = ' ';
            switch (tab[i][j].type) {
                case MT: symbole = 'T'; break; 
                case MD: symbole = 'D'; break;  
                case LT: symbole = '3'; break;  
                case LD: symbole = '2'; break;  
                default: symbole = ' '; break;  
            }
            if (symbole == ' ' || tab[i][j].c.lettre != ' ') {
                printf("| %c ", toupper(tab[i][j].c.lettre));
            } else{
                printf("| %c ", tolower(symbole));
            }
        }
        printf("|\n");
    }
    
    // Ligne inférieure finale
    for (int j = 0; j < TAILLE_PLATEAU; j++) {
        printf("+---");
    }
    printf("+\n");
}

void insert_caractere(caractere car, Case **tab, int x, int y) {
    if (tab[x][y].c.lettre == ' ') {  
        tab[x][y].c.lettre = car.lettre;  // ✅ Insère uniquement la lettre
        tab[x][y].c.score = car.score;    // ✅ Insère le score associé à cette lettre
        tab[x][y].c.nb = car.nb;          // ✅ Insère la quantité si nécessaire
    }
}

bool est_vide_case(Case **plateau, int x, int y) {
    if (x < 0 || x >= TAILLE_PLATEAU || y < 0 || y >= TAILLE_PLATEAU) {
        return true;
    }
    return plateau[x][y].c.lettre == ' ';
}

bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale, bool test) {
    int len = strlen(word);
    bool adjacent = false;

    if (est_verticale) {
        if (y + len > TAILLE_PLATEAU) {
            if (!test)
                printf("Le mot dépasse les limites du plateau (vertical)\n");
            return false;
        }

        for (int i = 0; i < len; i++) {
            if (!est_vide_case(plateau, x, y + i) && plateau[x][y + i].c.lettre != toupper(word[i])) {
                if (!test)
                    printf("Le mot ne peut pas être placé car il y a déjà un mot sur son chemin\n");
                return false;
            }
            if (x == (TAILLE_PLATEAU - 1) / 2 && (y + i) == (TAILLE_PLATEAU - 1) / 2) {
                adjacent = true;
            } else {
                if (!est_vide_case(plateau, x - 1, y + i)) adjacent = true;
                if (!est_vide_case(plateau, x + 1, y + i)) adjacent = true;
                if (!est_vide_case(plateau, x, y + i - 1)) adjacent = true;
                if (!est_vide_case(plateau, x, y + i + 1)) adjacent = true;
            }
        }
    } else {
        if (x + len > TAILLE_PLATEAU) {
            if(!test)
                printf("Le mot dépasse les limites du plateau (horizontal)\n");
            return false;
        }

        for (int i = 0; i < len; i++) {
            if (!est_vide_case(plateau, x + i, y) && plateau[x + i][y].c.lettre != toupper(word[i])) {
                if(!test)
                    printf("Le mot ne peut pas être placé car il y a deja un mot sur son chemin\n");
                return false;
            }
            if ((x + i) == (TAILLE_PLATEAU - 1) / 2 && y == (TAILLE_PLATEAU - 1) / 2) {
                adjacent = true;
            } else {
                if (!est_vide_case(plateau, x + i - 1, y)) adjacent = true;
                if (!est_vide_case(plateau, x + i + 1, y)) adjacent = true;
                if (!est_vide_case(plateau, x + i, y - 1)) adjacent = true;
                if (!est_vide_case(plateau, x + i, y + 1)) adjacent = true;
            }
        }
    }

    if (adjacent == false) {
        if(!test)
            printf("Le mot ne peut pas être placé ici (il n'est pas adjacent à un mot déjà placé et ne passe pas par le milieu)\n");
        return false;
    }
    
    if(!test)
        printf("Le mot peut être inséré\n");
    return true;
}

char *check_mot(int x, int y, bool est_verticale, Case **plateau) {
    char *mot = malloc((TAILLE_PLATEAU + 1) * sizeof(char));
    if (!est_vide_case(plateau, x, y)) {
        int i = 0;
        if (est_verticale) {
            while(!est_vide_case(plateau, x, y - i - 1)) {
                i++;
            }
            int j = 0;
            while(!est_vide_case(plateau, x, y - i)) {
                i--;
                mot[j] = plateau[x][y - i - 1].c.lettre;
                j++;
            }
        } else {
            while(!est_vide_case(plateau, x - i - 1, y)) {
                i++;
            }
            int j = 0;
            while(!est_vide_case(plateau, x - i, y)) {
                i--;
                mot[j] = plateau[x - i - 1][y].c.lettre;
                j++;
            }
        }
    }
    return mot;
}

int insert_mot(char *word, Case **plateau, int x, int y, bool est_verticale, int taille_dic, Joueur *joueur, bool test) {
    char **ListMot = malloc(16 * sizeof(char *));
    int e = 0;
    int points = 0;
    bool ok_chevalet;
    int nb_lettres_utilisees = 0;
    
    int len = strlen(word);
    bool use_lettre[len];
    caractere *mot = malloc((len + 1) * sizeof(caractere));
    int *placement[7];
    for (int i = 0; i < len; i++) {
        mot[i].lettre = toupper(word[i]);
    }

    if(!inserable(word, plateau, x, y, est_verticale, test)) {
        points = -1;
    } else {  
        if(est_verticale) {
            for(int i = 0; i < len; i++) {
                if(est_vide_case(plateau, x, y + i)) {
                    insert_caractere(mot[i], plateau, x, y + i);
                    use_lettre[i] = true;
                    nb_lettres_utilisees++;
                    if(!verif_chevalet(*joueur, mot[i].lettre)) {
                        ok_chevalet = false;
                    } else {
                        ok_chevalet = true;
                    }

                    ListMot[e] = check_mot(x, y + i, !est_verticale, plateau);
                    placement[e] = malloc(2 * sizeof(int));
                    placement[e][0] = x;
                    placement[e][1] = y + i;
                    e++;
                } else {
                    use_lettre[i] = false;
                }
            }
        } else {
            for(int i = 0; i < len; i++) {
                if(est_vide_case(plateau, x + i, y)) {
                    insert_caractere(mot[i], plateau, x + i, y);
                    use_lettre[i] = true;
                    nb_lettres_utilisees++;
                    if(!verif_chevalet(*joueur, mot[i].lettre)) {
                        ok_chevalet = false;
                    } else {
                        ok_chevalet = true;
                    }

                    ListMot[e] = check_mot(x + i, y, !est_verticale, plateau);
                    placement[e] = malloc(2 * sizeof(int));
                    placement[e][0] = x + i;
                    placement[e][1] = y;
                    e++;
                } else {
                    use_lettre[i] = false;
                }
            }
        }
    }

    if (points != -1) {
        ListMot[e] = check_mot(x, y, est_verticale, plateau);
        e++;
    }

    bool valide_dic = true;
    for(int i = 0; i < e; i++) {
        if (strlen(ListMot[i]) > 1) {
            if(!test)
                printf("Mot formé : %s\n", ListMot[i]);
            valide_dic = mot_valide(ListMot[i], taille_dic);
        }
    }

    if(valide_dic && ok_chevalet) {
        for (int i = 0; i < e; i++) {
            if(strlen(ListMot[i]) > 1) {
                points += calcul_points(ListMot[i], plateau, x, y, est_verticale);
            }
            free(ListMot[i]);
        }

        for (int i = 0; i < len; i++) {
            if (use_lettre[i] && !test) {
                retire_chevalet(joueur, mot[i].lettre);
            }
        }
    } else {
        if (!ok_chevalet) {
            if(!test)
                printf("Vous n'avez pas les bonnes lettres dans votre chevalet\n");
        } else {
            if(!test)
                printf("L'un des mots formés n'est pas dans le dictionnaire\n");
        }

        points = -1;
        for (int i = 0; i < e - 1; i++) {
            plateau[placement[i][0]][placement[i][1]].c = vide;
            free(placement[i]);
        }
    }

    if (points == -1) {
        if(!test)
            printf("Le mot n'a pas pu être placé, veuillez essayer à nouveau\n");
    } else {
        if (nb_lettres_utilisees == 7) {
            printf("Vous avez placé toutes les lettres de votre chevalet ! 50 points bonus\n");
            points += 50;
        }
        if(!test)
            printf("Vous avez obtenu %d points\n", points);
    }

    free(ListMot);
    free(mot);
    return points;
}

void ajout_mot(Case **plateau, Joueur *joueur, int taille_dic) {
    int x, y;
    char o;
    bool orientation = false;
    char mot[TAILLE_PLATEAU + 1];
    int points = -1;
    while (points == -1) {
        do {
            printf("Donnez un mot, ses coordonnées et son orientation (exemple : bonjour 3 4 v)\n");
            printf("Si vous voulez passer votre tour, entrez n\'importe quoi avec une orientation autre que \"v\" ou \"h\"\n");
            scanf("%s %d %d %c", mot, &x, &y, &o);
        } while (!mot_alpha(mot));

        if (toupper(o) != 'H' && toupper(o) != 'V') {
            points = 0;
        } else if (x >= TAILLE_PLATEAU || y >= TAILLE_PLATEAU || x < 0 || y < 0) {
            printf("Les coordonnées depassent la taille du tableau\n");
        } else {
            if (toupper(o) == 'H') {
                orientation = false;
            } else if (toupper(o) == 'V') {
                orientation = true;
            }

            points = insert_mot(mot, plateau, x, y, orientation, taille_dic, joueur, false);
        }
    }

    joueur->score_actuel += points;
    printf("Le score actuel est %d\n", joueur->score_actuel);

    retire_multiplicateur(plateau);
}

bool mot_alpha(char *mot) {
    int len = strlen(mot);
    for (int i = 0; i < len; i++) {
        if (!isalpha(mot[i])) {
            printf("Le mot contient des caractères interdits\n");
            return false;
        }
    }
    return true;
}

int get_score(char lettre) {
    lettre = toupper(lettre);
    for (int i = 0; i < 26; i++) {
        if (lettres[i].lettre == lettre) {
            return lettres[i].score;
        }
    }
    return 0; 
}

int calcul_points(char *word, Case **plateau, int x, int y, bool est_verticale) {
    int total = 0;
    int multiplicateur = 1;
    int len = strlen(word);

    caractere *mot = malloc((len + 1) * sizeof(caractere));

    for (int i = 0; i < len; i++) {
        mot[i].lettre = toupper(word[i]);
        mot[i].score = get_score(mot[i].lettre);
    }

    if (est_verticale) {
        int fy = y;
        while (!est_vide_case(plateau, x, fy - 1)) {
            fy--;
        }
        
        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            if (plateau[x][fy + i].type == LD && !plateau[x][fy + i].est_placee) {
                total += mot[i].score;   
                plateau[x][fy + i].est_placee = true;  
            } else if (plateau[x][fy + i].type == LT && !plateau[x][fy + i].est_placee) {
                total += mot[i].score * 2;  
                plateau[x][fy + i].est_placee = true;  
            }

            // Gestion des multiplicateurs de mots
            if (plateau[x][fy + i].type == MD && !plateau[x][fy + i].est_placee) {
                multiplicateur *= 2;  // Mot Double
                plateau[x][fy + i].est_placee = true;  
            } else if (plateau[x][fy + i].type == MT && !plateau[x][fy + i].est_placee) {
                multiplicateur *= 3;  // Mot Triple
                plateau[x][fy + i].est_placee = true; 
            }
        }
    } else {
        int fx = x;
        while (!est_vide_case(plateau, fx - 1, y)) {
            fx--;
        }

        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            
            if (plateau[fx + i][y].type == LD && !plateau[fx + i][y].est_placee) {
                total += mot[i].score;
                plateau[fx + i][y].est_placee = true;
            } else if (plateau[fx + i][y].type == LT && !plateau[fx + i][y].est_placee) {
                total += mot[i].score * 2;
                plateau[fx + i][y].est_placee = true;
            }
            
            if (plateau[fx + i][y].type == MD && !plateau[fx + i][y].est_placee) {
                multiplicateur *= 2;
                plateau[fx + i][y].est_placee = true;
            } 
            else if (plateau[fx + i][y].type == MT && !plateau[fx + i][y].est_placee) {
                multiplicateur *= 3;
                plateau[fx + i][y].est_placee = true;
            }
        }
    }

    total *= multiplicateur;
    printf("Le mot %s a rapporté %d points\n", word, total);
    free(mot);
    return total;
}

void retire_multiplicateur(Case **plateau) { 
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            if (!est_vide_case(plateau, i, j)) {
                plateau[i][j].type = N;
            }
        }
    }
}

void free_dic(int taille) {
    for (int i = 0; i < taille; i++) {
        free(dic[i]);
    }
}

int init_dictionnaire(char *dictionnaire) {
    FILE *file = fopen(dictionnaire, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du dictionnaire\n");
    }

    char ligne[30];
    int i = 0;
    while (fgets(ligne, sizeof(ligne), file) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0';  // Supprime le saut de ligne
        if(strlen(ligne) <= TAILLE_PLATEAU) {
            dic[i] = malloc(strlen(ligne + 1) * sizeof(char *));
            strcpy(dic[i], ligne);
            i++;
        }
    }

    fclose(file);
    return i;
}

bool peut_placer(char *mot, int x, int y, bool est_verticale, Joueur joueur, Case **plateau) {
    if (inserable(mot, plateau, x, y, est_verticale, true)) {
        int len = strlen(mot);
        char *liste_lettre = malloc((len + 1) * sizeof(char));
        int l = 0;
        for(int i = 0; i < len; i++) {
            if(est_verticale) {
                if (plateau[x][y + i].c.lettre == ' ') {
                    liste_lettre[l] = toupper(mot[i]);
                    l++;
                }
            } else {
                if (plateau[x + i][y].c.lettre == ' ') {
                    liste_lettre[l] = toupper(mot[i]);
                    l++;
                }
            }
        }

        if (verif_chevalet_liste(joueur, liste_lettre, l)) {
            free(liste_lettre);
            return true;
        } else {
            free(liste_lettre);
        }
    }

    return false;
}

void meilleur_mot(Joueur joueur, int taille_dic, Case **plateau) {
    int points = 0;
    char mot[TAILLE_PLATEAU + 1];
    int jx, jy;
    bool orientation;
    for (int x = 0; x < TAILLE_PLATEAU; x++) {
        for (int y = 0;y < TAILLE_PLATEAU; y++) {
            for (int i = 0; i < taille_dic; i++) {
                if (peut_placer(dic[i], x, y, true, joueur, plateau)) {
                    Case copie_plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            copie_plateau[i][j] = plateau[i][j];
                        }
                    }

                    int pts=insert_mot(dic[i], plateau, x, y, true, taille_dic, &joueur, true);
                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            plateau[i][j] = copie_plateau[i][j];
                        }
                    }

                    if (pts > points) {
                        points = pts;
                        strcpy(mot, dic[i]);
                        jx = x;
                        jy = y;
                        orientation = true;
                    }
                }

                if (peut_placer(dic[i], x, y, false, joueur, plateau)) {
                    Case copie_plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            copie_plateau[i][j] = plateau[i][j];
                        }
                    }

                    int pts = insert_mot(dic[i], plateau, x, y, false, taille_dic, &joueur, true);
                    for (int i = 0; i < TAILLE_PLATEAU; i++) {
                        for (int j = 0; j < TAILLE_PLATEAU; j++) {
                            plateau[i][j] = copie_plateau[i][j];
                        }
                    }

                    if (pts > points) {
                        points = pts;
                        strcpy(mot, dic[i]);
                        jx = x;
                        jy = y;
                        orientation = true;
                    }
                }
            }
        }
    }

    if (points == 0) {
        printf("Aucun mot valide trouvé\n");
    } else if (orientation) {
        printf("Le meilleur mot est %s aux coordonnées %d %d, orienté verticalement, et il rapporte %d points\n", mot, jy, jx, points);
    } else {
        printf("Le meilleur mot est %s aux coordonnées %d %d, orienté horizontalement, et il rapporte %d points\n", mot, jy, jx, points);
    }
}

char *majuscule_mot(char *mot) {
    char *mot_majuscule = malloc(strlen(mot) + 1);  // +1 pour le caractère nul '\0'
    if (mot_majuscule == NULL) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; mot[i] != '\0'; i++) {
        mot_majuscule[i] = toupper(mot[i]);
    }
    mot_majuscule[strlen(mot)] = '\0';  // Ajoute le caractère de fin de chaîne

    return mot_majuscule;
}

bool mot_valide(char *word , int taille) {
    for (int i = 0; i < taille; i++) {
        if (strcmp(majuscule_mot(word), dic[i]) == 0) {
            printf("Le mot %s est valide\n", word);
            return true;
        }
    }
    printf("Le mot %s n'est pas valide\n", word);
    return false;
}

void init_sac() {
    int nb = 0;

    for (int i = 0; i < 26; i++) {
        nb += lettres[i].nb;
    }

    sac = malloc(nb * sizeof(caractere));
    int k = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < lettres[i].nb; j++) {
            sac[k] = lettres[i];
            k++;
        }
    }
}

caractere pioche() {
    if (nb_pioche <= 0) {
        printf("Le sac est vide, impossible de piocher.\n");
        return vide;
    }

    int c = rand() % nb_pioche;
    caractere car = sac[c];
    caractere temp = sac[nb_pioche-1];
    sac[c] = temp;
    sac[nb_pioche-1] = car;
    nb_pioche--;
    return car;
}

void init_chevalet(Joueur *joueur) {
    joueur->chevalet_joueur.nblettres = 7;
    for (int i = 0; i < 7; i++) {
        joueur->chevalet_joueur.lettres[i] = pioche();
    }
}

void affiche_chevalet(Joueur joueur) {
    printf("Votre chevalet contient :\n");
    for (int i = 0; i < 7; i++) {
        printf("%c ", joueur.chevalet_joueur.lettres[i].lettre);
    }
    printf("\n");
}

bool verif_chevalet(Joueur joueur, char lettre) {
    for (int i = 0; i < 7; i++) {
        if(joueur.chevalet_joueur.lettres[i].lettre == lettre) {
            return true;
        }
    }
    return false;
}

bool verif_chevalet_liste(Joueur joueur, char *liste, int taille) {
    bool pris[7] = {false};
    bool trouve = false;
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < 7; j++) {
            if (joueur.chevalet_joueur.lettres[j].lettre == liste[i] && !pris[j]) {
                pris[j] = true;
                trouve = true;
                break;
            }
        }

        if (!trouve) {
            return false;
        }
        trouve = false;
    }

    return true;
}

void retire_chevalet(Joueur *joueur, char lettre) {
    affiche_chevalet(*joueur);
    for (int i = 0; i < 7; i++) {
        if (joueur->chevalet_joueur.lettres[i].lettre == lettre) {
            joueur->chevalet_joueur.lettres[i] = vide;
            break;
        }
    }

    affiche_chevalet(*joueur);
}

void remplir_chevalet(Joueur *joueur) {
    for (int i = 0; i < 7; i++) {
        if(joueur->chevalet_joueur.lettres[i].lettre == ' ') {
            joueur->chevalet_joueur.lettres[i] = pioche();
            if (nb_pioche <= 0) {
                printf("Le sac est vide\n");
                break;
            }
        }
    }
}

bool vide_chevalet(Joueur joueur) {
    for (int i = 0; i < 7; i++) {
        if (joueur.chevalet_joueur.lettres[i].lettre != ' ') {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));  // Initialisation de la graine pour la génération aléatoire

    int taille_dic = init_dictionnaire("dictionnaire.txt");
    bool b = true;
    int n;

    Case **plateau = init_plateau(); 
    init_case_mot_triple_plateau(plateau, coordonnees_cases_mot_triple);
    init_case_mot_double_plateau(plateau, coordonnees_cases_mot_double);
    init_case_lettre_double_plateau(plateau, coordonnees_cases_lettre_double);
    init_case_lettre_triple_plateau(plateau, coordonnees_cases_lettre_triple);
    affiche_tab(plateau);

    init_sac();

    Joueur joueur1;
    joueur1.score_actuel = 0;
    init_chevalet(&joueur1);

    Joueur joueur2;
    joueur2.score_actuel = 0;
    init_chevalet(&joueur2);

    int tour = 0;
    bool fin = false;

    while(b) {
        if (tour % 2 == 0) {
            remplir_chevalet(&joueur1);
            if (vide_chevalet(joueur1)) {
                printf("Fin de la partie\n");
                fin = true;
            } else {
                printf("Tour du joueur 1\n");
                affiche_chevalet(joueur1);

                int reponse;
                printf("Voulez-vous calculer le mot rapportant le plus de points ? (1 pour oui)\n");
                scanf("%d", &reponse);
                if (reponse == 1) {
                    meilleur_mot(joueur1, taille_dic, plateau);
                }

                ajout_mot(plateau, &joueur1, taille_dic);
                affiche_tab(plateau);
            }
        } else {
            remplir_chevalet(&joueur2);
            if (vide_chevalet(joueur2)) {
                printf("Fin de la partie\n");
                fin = true;
            } else {
                printf("Tour du joueur 2\n");
                affiche_chevalet(joueur2);

                int reponse;
                printf("Voulez-vous calculer le mot rapportant le plus de points ? (1 pour oui)\n");
                scanf("%d", &reponse);
                if (reponse == 1) {
                    meilleur_mot(joueur2, taille_dic, plateau);
                }

                ajout_mot(plateau, &joueur2, taille_dic);
                affiche_tab(plateau);
            }
        }
        tour++;

        if (!fin) {
            printf("1 pour continuer, 0 pour quitter\n");
            scanf("%d", &n);
            if (n == 0)
                b = false;
        } else {
            b = false;
            printf("Score final du joueur 1 : %d\n", joueur1.score_actuel);
            printf("Score final du joueur 2 : %d\n", joueur2.score_actuel);
            if (joueur1.score_actuel > joueur2.score_actuel) {
                printf("Le joueur 1 a gagné !\n");
            } else if (joueur2.score_actuel > joueur1.score_actuel) {
                printf("Le joueur 2 a gagné !\n");
            } else {
                printf("Égalité entre les deux joueurs !\n");
            }
        }
    }

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        free(plateau[i]);
    }
    free(plateau);
    free_dic(taille_dic);

    return 0;
}