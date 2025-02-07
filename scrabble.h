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

#endif 


