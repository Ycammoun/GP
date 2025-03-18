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

}Joueur;

typedef struct {
    int x;
    int y;
}couple;



Case **init_plateau(int TAILLE_PLATEAU);
void affiche_tab(Case **tab);
void insert_caractere(caractere car,Case **tab,int x,int y);
void ajout_caractere(Case **tab);
bool est_vide_case(Case **plateau ,int x , int y);
bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale);
void insert_mot(char *word,Case **plateau,int x,int y, bool est_verticale);
void ajout_mot(Case **plateau,Joueur *joueur);
bool mot_alpha(char *mot);
int calcul_points(char *word,Case **plateau,int x,int y, bool est_verticale);
void init_case_triple_plateau(Case **plateau,couple cordonnees[]);
void init_case_double_plateau(Case **plateau,couple cordonnees[]);
void init_case_lettre_double_plateau(Case **plateau,couple cordonnees[]);
void init_case_lettre_triple_plateau(Case **plateau,couple cordonnees[]);
void affiche_tab1(Case **tab);
void free_plateau(Case **plateau);






#endif 


