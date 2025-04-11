#ifndef SCRABBLE_H
#define SCRABBLE_H
//gcc -o scrabble_program scrabble.c
//./scrabble_program 

typedef enum {N, LD, LT, MD, MT} type_case;

typedef struct {
    char lettre;  
    int nb;      
    int score;    
} caractere;

typedef struct {
    type_case type;   
    caractere c;  
    bool est_placee;    
} Case;

typedef struct {
    int nblettres;       
    caractere lettres[7]; 
} Chevalet;

typedef struct {
    int score_actuel;
    Chevalet chevalet_joueur;
} Joueur;

typedef struct {
    int x;
    int y;
} couple;

Case **init_plateau();
void init_case_lettre_double_plateau(Case **plateau, couple coordonnees[]);
void init_case_lettre_triple_plateau(Case **plateau, couple coordonnees[]);
void init_case_mot_double_plateau(Case **plateau, couple coordonnees[]);
void init_case_mot_triple_plateau(Case **plateau, couple coordonnees[]);

void affiche_tab(Case **tab);
void insert_caractere(caractere car, Case **tab, int x, int y);
bool est_vide_case(Case **plateau, int x, int y);

bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale, bool test);
char *check_mot(int x, int y, bool est_verticale, Case **plateau);
int insert_mot(char *word, Case **plateau, int x, int y, bool est_verticale, int taille_dic, Joueur *joueur, bool test);
void ajout_mot(Case **plateau, Joueur *joueur, int taille_dic);

bool mot_alpha(char *mot);
int get_score(char lettre);
int calcul_points(char *word, Case **plateau, int x, int y, bool est_verticale, bool test);
void retire_multiplicateur(Case **plateau);

void free_dic(int taille);
int init_dictionnaire(char *dictionnaire);
bool peut_placer(char* mot, int x, int y, bool est_verticale, Joueur joueur, Case** plateau);
void meilleur_mot(Joueur joueur, int taille_dic, Case **plateau);
char* majuscule_mot(char *mot);
bool mot_valide(char *word, int taille, bool test);

caractere pioche();
void init_chevalet(Joueur *joueur);
void affiche_chevalet(Joueur joueur);
bool verif_chevalet(Joueur joueur, char lettre);
bool verif_chevalet_liste(Joueur joueur, char *liste, int taille);
void retire_chevalet(Joueur *joueur, char lettre);
void remplir_chevalet(Joueur *joueur);
bool vide_chevalet(Joueur joueur);

#endif 


