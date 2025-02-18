#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "scrabble.h"
    caractere lettres[26] = {
        {'A', 9, 1}, {'B', 2, 3}, {'C', 2, 3}, {'D', 3, 2}, {'E', 15, 1}, 
        {'F', 2, 4}, {'G', 2, 2}, {'H', 2, 4}, {'I', 8, 1}, {'J', 1, 8}, 
        {'K', 1, 10}, {'L', 5, 1}, {'M', 3, 2}, {'N', 6, 1}, {'O', 6, 1}, 
        {'P', 2, 3}, {'Q', 1, 8}, {'R', 6, 1}, {'S', 6, 1}, {'T', 6, 1}, 
        {'U', 6, 1}, {'V', 2, 4}, {'W', 1, 10}, {'X', 1, 10}, {'Y', 1, 10}, 
        {'Z', 1, 10}
    };

caractere vide = {' ', 9, 1};  
couple cordonnees_case_mots_triple[8]={
        {0, 0}, {0, 7}, {0, 14}, {7, 0},
        {7, 14}, {14, 0}, {14, 7}, {14, 14}
};
couple cordonnees_case_mots_double[16]={
    {1,1}, {2,2}, {3, 3}, {4,4},{13,1},{12 , 2},
    {11, 3}, {10, 4}, {4,10},{3,11}, {2,12}, {1,13},
    {10,10},{11,11},{12,12},{13,13}
};
const int TAILLE_PLATEAU = 15;

Case **init_plateau(int TAILLE_PLATEAU) {
    Case **resultat = malloc(TAILLE_PLATEAU * sizeof(Case *));
    if (!resultat) {
        perror("Erreur d'allocation mémoire pour le plateau \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        resultat[i] = malloc(TAILLE_PLATEAU * sizeof(Case));
        if (!resultat[i]) {
            perror("Erreur d'allocation mémoire pour une ligne du plateau \n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            resultat[i][j].type = N;  
            resultat[i][j].c = vide;     
        }
    }

    return resultat;
}
void init_case_triple_plateau(Case **plateau,couple cordonnees[]){
    for (int i =0 ;i < 8; i++){
        int x=cordonnees[i].x;
        int y=cordonnees[i].y;
        plateau[x][y].type=MT;
    }
    //return plateau;

}
void init_case_double_plateau(Case **plateau,couple cordonnees[]){
    for (int i =0 ;i < 16; i++){
        int x=cordonnees[i].x;
        int y=cordonnees[i].y;
        plateau[x][y].type=MD;
    }
    //return plateau;

}




/*void affiche_tab(Case **tab) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            printf("%c ", tab[i][j].c.lettre);  
        }
        printf("\n");
    }
    }*/

void affiche_tab(Case **tab) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        // Ligne supérieure des cases
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            printf("+---");
        }
        printf("+\n");

        // Contenu des cases
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
	  printf("| %c ", tab[i][j].c.lettre);
        }
        printf("|\n");
    }
    
    // Ligne inférieure finale
    for (int j = 0; j < TAILLE_PLATEAU; j++) {
        printf("+---");
    }
    printf("+\n");
}

void affiche_tab1(Case **tab) {
    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < TAILLE_PLATEAU; j++) {
            char symbole;
            switch (tab[i][j].type) {
                case MT: symbole = 'T'; break; 
                case MD: symbole = 'D'; break;  
                case LT: symbole = '3'; break;  
                case LD: symbole = '2'; break;  
                default: symbole = ' '; break;  
            }
            printf("| %c ", symbole);
        }
        printf("|\n");
    }
    
    for (int j = 0; j < TAILLE_PLATEAU; j++) {
        printf("+---");
    }
    printf("+\n");
}



void insert_caractere(caractere car,Case **tab,int x,int y){
    if(tab[y][x].c.lettre!=' ')
        printf("case n'est pas vide \n");
    else {
        tab[y][x].c=car;
    }
}
void ajout_caractere(Case **tab){
    int x,y;
    char car;
    printf("donnez un caractere et ses cordonnées (exemple e 3 4) \n");
    scanf("%c %d %d",&car,&x,&y);
    if(x>=TAILLE_PLATEAU || y>=TAILLE_PLATEAU ||x<0 ||y<0){
        printf("cordonnées  depassent la taille du tableau \n");
    }
    else if(! isalpha(car))
    printf("le caractere n est pas une lettre \n");
    else {
    int upchar=toupper(car);
    insert_caractere(lettres[upchar-65],tab,x,y);
    }
}

bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale) {
    int len = strlen(word);

    if (est_verticale) {
        if (y+len > TAILLE_PLATEAU) {
            printf("Le mot dépasse les limites du plateau (vertical).\n");
            return false;
        }
    } else {
        if (x+len > TAILLE_PLATEAU) {
            printf("Le mot dépasse les limites du plateau (horizontal).\n");
            return false;
        }
    }

    printf("Le mot peut être inséré.\n");
    return true;
}

void insert_mot(char *word,Case **plateau,int x,int y, bool est_verticale){
    int len=strlen(word);
    caractere *mot=malloc(len*sizeof(caractere));
    for(int i=0;i<len;i++){
        mot[i].lettre=word[i];
    }
    if(!inserable(word,plateau,x,y,est_verticale)){
        printf("Le mot ne peut pas être placé car il dépasse les bords du plateau.\n");
        exit(EXIT_FAILURE);
    }
    else{
        
        if(est_verticale){
            for(int i =0;i<len;i++){
                insert_caractere(mot[i],plateau,x,y+i);
            }

        }
        else{
            for(int i =0;i<len;i++){
                insert_caractere(mot[i],plateau,x+i,y);
            }

        }
    }
    free(mot);
}







int main() {
    bool b=true;
    int n;
    Case **plateau = init_plateau(TAILLE_PLATEAU); 
    init_case_triple_plateau(plateau,cordonnees_case_mots_triple);
    init_case_double_plateau(plateau,cordonnees_case_mots_double);

    affiche_tab1(plateau);
    while(b){
    inserable("hello",plateau,0,0,true);
    insert_mot("hello",plateau,0,0,true);
    insert_mot("bonjour",plateau,2,2,false);
    ajout_caractere(plateau);
    affiche_tab(plateau);
    printf("1 pour continuer 0 pour quitter \n");
    scanf("%d",&n);
    if(n==0)
    b=false;

    }


    

    for (int i = 0; i < TAILLE_PLATEAU; i++) {
        free(plateau[i]);
    }
    free(plateau);

    return 0;
}


