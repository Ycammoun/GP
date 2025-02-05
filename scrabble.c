#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <ctype.h>
#include <stdbool.h>
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
	  //printf("|   ");
        }
        printf("|\n");
    }
    
    // Ligne inférieure finale
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
    printf("donnez un caractere et ses cordonnes (exemple e 3 4) \n");
    scanf("%c %d %d",&car,&x,&y);
    if(x>=TAILLE_PLATEAU || y>=TAILLE_PLATEAU ||x<0 ||y<0){
        printf("cordonné  depasse la taille du tableau \n");
    }
    else if(! isalpha(car))
    printf("le caractere n est pas une lettre \n");
    else {
    int upchar=toupper(car);
    insert_caractere(lettres[upchar-65],tab,x,y);
    }
}







int main() {
    bool b=true;
    int n;
    Case **plateau = init_plateau(TAILLE_PLATEAU); 
    affiche_tab(plateau);
    while(b){
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


