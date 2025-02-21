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
couple cordonnees_cases_lettres_double[24]={
    {3,0},{11,0},{6,2},{8,2},{0,3},{7,3},{14,3},{2,6},{6,6},{8,6},{12,6},{3,7},{11,7},{2,8},{6,8},{8,8},
    {12,8},{0,11},{7,11},{14,11},{6,12},{8,12},{3,14},{11,14}
};
couple cordonnees_cases_lettres_triples[12]={
    {5,1},{9,1},{1,5},{5,5},{9,5},{13,5},{1,9},{5,9},{9,9},{13,9},{5,13},{9,13}
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
void init_case_lettre_double_plateau(Case **plateau,couple cordonnees[]){
    for (int i =0 ;i < 24; i++){
        int x=cordonnees[i].x;
        int y=cordonnees[i].y;
        plateau[x][y].type=LD;
    }
    //return plateau;

}
void init_case_lettre_triple_plateau(Case **plateau,couple cordonnees[]){
    for (int i =0 ;i < 12; i++){
        int x=cordonnees[i].x;
        int y=cordonnees[i].y;
        plateau[x][y].type=LT;
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
    for (int j = 0; j < TAILLE_PLATEAU; j++) {
        // Ligne supérieure des cases
        for (int i = 0; i < TAILLE_PLATEAU; i++) {
            printf("+---");
        }
        printf("+\n");

        // Contenu des cases
        for (int i = 0; i < TAILLE_PLATEAU; i++) {
            char symbole;
            switch (tab[i][j].type) {
                case MT: symbole = 'T'; break; 
                case MD: symbole = 'D'; break;  
                case LT: symbole = '3'; break;  
                case LD: symbole = '2'; break;  
                default: symbole = ' '; break;  
            }
            if (symbole==' ' ||tab[i][j].c.lettre !=' ' ){
                printf("| %c ", toupper(tab[i][j].c.lettre));

            }
            else{
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
    if(tab[x][y].c.lettre==' ')
        tab[x][y].c=car;
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
bool est_vide_case(Case **plateau ,int x , int y){
    return plateau[x][y].c.lettre==' ';
}

bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale) {
    int len = strlen(word);

    if (est_verticale) {
        if (y+len > TAILLE_PLATEAU) {
            printf("Le mot dépasse les limites du plateau (vertical).\n");
            return false;
        }
        for(int i=0;i<len;i++){
            if(!est_vide_case(plateau,x,y+i)&& plateau[x][y+i].c.lettre!=toupper(word[i])){
                printf("le mot ne peut pas etre place car il y a deja un mot sur son chemin\n ");

                return false;
            }
  

        }
    } else {
        if (x+len > TAILLE_PLATEAU) {
            printf("Le mot dépasse les limites du plateau (horizontal).\n");
            return false;
        }
        for(int i=0;i<len;i++){
            if(!est_vide_case(plateau,x+i,y)&& plateau[x+i][y].c.lettre!=toupper(word[i])){
                printf("le mot ne peut pas etre place car il y a deja un mot sur son chemin \n");

                return false;
            }
        }
    }


    printf("Le mot peut être inséré.\n");
    return true;
}

void insert_mot(char *word,Case **plateau,int x,int y, bool est_verticale){
    
    int len=strlen(word);
    caractere *mot=malloc(len*sizeof(caractere));
    for(int i=0;i<len;i++){
        mot[i].lettre=toupper(word[i]);
    }
    if(!inserable(word,plateau,x,y,est_verticale)){
        printf("Le mot ne peut pas être placé .\n");
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
void ajout_mot(Case **plateau){
    int x,y;
    char o;
    bool orientation =false;
    char mot[TAILLE_PLATEAU];
    do{
    printf("donnez un mot et ses cordonnées et son orientation  (exemple bonjour 3 4 v) \n");
    scanf("%s %d %d %c",mot,&x,&y,&o);
    }
    while(!mot_alpha(mot));

    
    if(toupper(o)!='H' && toupper(o)!='V'){
        printf("orientation non valide\n");
    } else     if(x>=TAILLE_PLATEAU || y>=TAILLE_PLATEAU ||x<0 ||y<0){
        printf("cordonnées  depassent la taille du tableau \n");
    } else{

    
    if(toupper(o)=='H'){
        orientation=false;
    }
    else if (toupper(o)=='V'){
        orientation=true;
    }



    //else if(! isalpha(car))
    //printf("le caractere n est pas une lettre \n");
    //else {
    insert_mot(mot,plateau,x,y,orientation);
    //}
    }
}
bool mot_alpha(char *mot){
    int len =strlen(mot);
    for(int i=0;i<len;i++){
        if(!isalpha(mot[i])){
            printf("le mot contient des caracteres interdits \n");
            return false;
        }
    }
    return true;
}







int main() {
    bool b=true;
    int n;
    Case **plateau = init_plateau(TAILLE_PLATEAU); 
    init_case_triple_plateau(plateau,cordonnees_case_mots_triple);
    init_case_double_plateau(plateau,cordonnees_case_mots_double);
    init_case_lettre_double_plateau(plateau,cordonnees_cases_lettres_double);
    init_case_lettre_triple_plateau(plateau,cordonnees_cases_lettres_triples);
    affiche_tab(plateau);

    //affiche_tab1(plateau);
    while(b){
    //inserable("hello",plateau,0,0,true);
    //insert_mot("hello",plateau,0,0,true);


    //insert_mot("lit",plateau,0,2,false);
    //ajout_caractere(plateau);
    ajout_mot(plateau);
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


