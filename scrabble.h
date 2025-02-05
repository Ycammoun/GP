#ifndef SCRABBLE_H
#define SCRABBLE_H


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
    Case **tab;  
} Plateau;

#endif 


