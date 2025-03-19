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
couple cordonnees_case_mots_double[17]={
    {1,1}, {2,2}, {3, 3}, {4,4},{13,1},{12 , 2},
    {11, 3}, {10, 4}, {4,10},{3,11}, {2,12}, {1,13},
    {10,10},{11,11},{12,12},{13,13},{7,7}
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
            resultat[i][j].est_placee = false;     
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
    for (int i =0 ;i < 17; i++){
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
            char symbole = ' ';
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



/*void insert_caractere(caractere car,Case **tab,int x,int y){
    if(tab[x][y].c.lettre==' ')
        tab[x][y].c=car;
}*/
void insert_caractere(caractere car, Case **tab, int x, int y) {
    if (tab[x][y].c.lettre == ' ') {  
        tab[x][y].c.lettre = car.lettre;  // ✅ Insère uniquement la lettre
        tab[x][y].c.score = car.score;    // ✅ Insère le score associé à cette lettre
        tab[x][y].c.nb = car.nb;          // ✅ Insère la quantité si nécessaire
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
bool est_vide_case(Case **plateau ,int x , int y){
    if (x < 0 || x >= TAILLE_PLATEAU || y < 0 || y >= TAILLE_PLATEAU) {
        return true;
    }
    return plateau[x][y].c.lettre==' ';
}

bool inserable(char *word, Case **plateau, int x, int y, bool est_verticale) {
    int len = strlen(word);
    bool adjacent = false;

    if (est_verticale) {
        if (y+len > TAILLE_PLATEAU) {
            printf("Le mot dépasse les limites du plateau (vertical).\n");
            return false;
        }
        for(int i=0;i<len;i++){
            if(!est_vide_case(plateau,x,y+i)&& plateau[x][y+i].c.lettre!=toupper(word[i])){
                printf("le mot ne peut pas etre place car il y a deja un mot sur son chemin\n");
                return false;
            }
            if (x == (TAILLE_PLATEAU - 1) / 2 && (y+i) == (TAILLE_PLATEAU - 1) / 2) {
                adjacent = true;
            } else {
                if (!est_vide_case(plateau, x - 1, y + i)) adjacent = true;
                if (!est_vide_case(plateau, x + 1, y + i)) adjacent = true;
                if (!est_vide_case(plateau, x, y + i - 1)) adjacent = true;
                if (!est_vide_case(plateau, x, y + i + 1)) adjacent = true;
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
            if ((x+i) == (TAILLE_PLATEAU - 1) / 2 && y == (TAILLE_PLATEAU - 1) / 2) {
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
        printf("Le mot ne peut pas être placé ici (il n'est pas adjacent et ne passe pas par le milieu)\n");
        return false;
    }
    printf("Le mot peut être inséré.\n");
    return true;
}
char *check_mot(int x,int y , bool est_verticale,Case **plateau)
{
    char *mot=malloc((TAILLE_PLATEAU+1)*sizeof(char));
    if(est_vide_case(plateau,x,y)){
        printf("la case est vide \n");
    }
    else{
        int i=0;
        if (est_verticale){
            while(!est_vide_case(plateau,x,y-i-1)){
                i++;
            }
            int j=0;
            while(!est_vide_case(plateau,x,y-i)){
                i--;
                mot[j]=plateau[x][y-i-1].c.lettre;
                j++;
                
            }


            

        }
        else{
            while(!est_vide_case(plateau,x-i-1,y)){
                i++;
            }
            int j=0;
            while(!est_vide_case(plateau,x-i,y)){
                i--;
                mot[j]=plateau[x-i-1][y].c.lettre;
                j++;
                
            }

        }
    }
    return mot;
    
}


int insert_mot(char *word,Case **plateau,int x,int y, bool est_verticale){

    char **ListMot =malloc(16*sizeof(char *));
    int e=0;
    int points=0;
    
    int len=strlen(word);
    caractere *mot=malloc((len+1)*sizeof(caractere));
    for(int i=0;i<len;i++){
        mot[i].lettre=toupper(word[i]);
    
    }
    if(!inserable(word,plateau,x,y,est_verticale)){
        points=-1;
    }
    else{
        
        if(est_verticale){
            for(int i =0;i<len;i++){
                if(est_vide_case(plateau,x,y+i)){
                    insert_caractere(mot[i],plateau,x,y+i);
                    ListMot[e]=check_mot(x,y+i,!est_verticale,plateau);
                    if(strlen(ListMot[e])>1)
                        points+=calcul_points1(ListMot[e],plateau,x,y+i,!est_verticale);
                    e++;
                }
                
            }

        }
        else{
            for(int i =0;i<len;i++){
                if(est_vide_case(plateau,x+i,y)){
                    insert_caractere(mot[i],plateau,x+i,y);
                    ListMot[e]=check_mot(x+i,y,!est_verticale,plateau);
                    if (strlen(ListMot[e])>1){
                        points+=calcul_points1(ListMot[e],plateau,x+i,y,!est_verticale);
                    }
                    e++;
                }
                
            }

        }
    }

    if(points!=-1){
        ListMot[e]=check_mot(x,y,est_verticale,plateau);
        if(strlen(ListMot[e])>1){
            points+=calcul_points1(ListMot[e],plateau,x,y,est_verticale);
        }
        e++;
    }
    printf("liste des mots formées\n");
    for(int i=0;i<e;i++){
        if(strlen(ListMot[i])>1){
            printf("%s \n",ListMot[i]);
        }
        free(ListMot[i]);


    }
    if(points==-1)
    
        printf("le mot n'a pas pu être placé, veuillez essayer à nouveau \n");
    
    else
        printf("le mot a rapporté %d points \n",points);
    
    free(ListMot);
    free(mot);
    return points;


}
void ajout_mot(Case **plateau,Joueur *joueur){
    int x,y;
    char o;
    bool orientation =false;
    char mot[TAILLE_PLATEAU+1];
    int points=-1;
    while(points==-1){
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
        points=insert_mot(mot,plateau,x,y,orientation);
    }
}
        joueur->score_actuel+=points;
        printf("le score actuel est %d \n",joueur->score_actuel);

        removeMultiplicateur(plateau);

    
    
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

    caractere *mot = malloc((len+1) * sizeof(caractere));

    for (int i = 0; i < len; i++) {
        mot[i].lettre = toupper(word[i]);
        mot[i].score = get_score(mot[i].lettre);
    }

    if (est_verticale) {
        int fy = y;
        while (!est_vide_case(plateau, x, fy-1)) {
            fy--;
        }

        
        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            if (plateau[x][fy + i].type == LD && !plateau[x][fy + i].est_placee) {
                total += mot[i].score;   
                plateau[x][fy + i].est_placee = true;  
            } 
            else if (plateau[x][fy + i].type == LT && !plateau[x][fy + i].est_placee) {
                total += mot[i].score * 2;  
                plateau[x][fy + i].est_placee = true;  
            }
            printf(" %d points.\n", total);

            // Gestion des multiplicateurs de mots
            if (plateau[x][fy + i].type == MD && !plateau[x][fy + i].est_placee) {
                multiplicateur *= 2;  // Mot Double
                plateau[x][fy + i].est_placee = true;  
            } 
            else if (plateau[x][fy + i].type == MT && !plateau[x][fy + i].est_placee) {
                multiplicateur *= 3;  // Mot Triple
                plateau[x][fy + i].est_placee = true; 
            }
        }
    } else {
        int fx = x;
        while (!est_vide_case(plateau, fx-1, y)) {
            fx--;
        }
        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            
            if (plateau[fx + i][y].type == LD && !plateau[fx + i][y].est_placee) {
                total += mot[i].score;   
                plateau[fx + i][y].est_placee = true;  
            } 
            else if (plateau[fx + i][y].type == LT && !plateau[fx + i][y].est_placee) {
                total += mot[i].score * 2; 
                plateau[fx + i][y].est_placee = true;  
            }
            printf(" %d points.\n", total);

            
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
    printf("Le mot %s a rapporté %d points.\n", word, total);
    free(mot);
    return total;
}



int calcul_points1(char *word, Case **plateau, int x, int y, bool est_verticale) {
    int total = 0;
    int multiplicateur = 1;
    int len = strlen(word);

    caractere *mot = malloc((len+1) * sizeof(caractere));

    for (int i = 0; i < len; i++) {
        mot[i].lettre = toupper(word[i]);
        mot[i].score = get_score(mot[i].lettre);
    }

    if (est_verticale) {
        int fy = y;
        while (!est_vide_case(plateau, x, fy-1)) {
            fy--;
        }

        
        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            if (plateau[x][fy + i].type == LD ) {
                total += mot[i].score;   
            } 
            else if (plateau[x][fy + i].type == LT ) {
                total += mot[i].score * 2;  
            }
            printf(" %d points.\n", total);

            // Gestion des multiplicateurs de mots
            if (plateau[x][fy + i].type == MD ) {
                multiplicateur *= 2;  // Mot Double
          
            } 
            else if (plateau[x][fy + i].type == MT ) {
                multiplicateur *= 3;  // Mot Triple
            }
        }
    } else {
        int fx = x;
        while (!est_vide_case(plateau, fx-1, y)) {
            fx--;
        }
        for (int i = 0; i < len; i++) {
            total += mot[i].score;  

            
            if (plateau[fx + i][y].type == LD ) {
                total += mot[i].score;   
            } 
            else if (plateau[fx + i][y].type == LT ) {
                total += mot[i].score * 2; 
            }
            printf(" %d points.\n", total);

            
            if (plateau[fx + i][y].type == MD ) {
                multiplicateur *= 2;  
            } 
            else if (plateau[fx + i][y].type == MT) {
                multiplicateur *= 3;  
            }
        }
    }

    total *= multiplicateur;
    printf("Le mot %s a rapporté %d points.\n", word, total);
    free(mot);
    return total;
}
void removeMultiplicateur(Case **plateau){
    
    for(int i=0;i<TAILLE_PLATEAU;i++){
        for(int j=0;j<TAILLE_PLATEAU;j++){
            if(!est_vide_case(plateau,i,j)){
                plateau[i][j].type=N;


            }
        }
    }
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

    Joueur joueur1;
    joueur1.score_actuel=0;
    //joueur1.chevalet_joueur.nblettres=0;
    //joueur1.chevalet_joueur.lettres[7];
    Joueur joueur2;
    joueur2.score_actuel=0;
    int tour=0;
    //affiche_tab1(plateau);
    while(b){
        if(tour%2==0){
            printf("joueur 1 \n");
            ajout_mot(plateau,&joueur1);
            affiche_tab(plateau);


        }
        else{
            printf("joueur 2 \n");
            ajout_mot(plateau,&joueur2);

            affiche_tab(plateau);


        }
        tour++;


    //ajout_mot(plateau);
    //affiche_tab(plateau);
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


