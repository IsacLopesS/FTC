#include<string.h>
#include<stdlib.h>

#define estado_mod 10

typedef struct{
    char nomeEstado[estado_mod];
    char final; //s -> sim / n-> nao
    char inicial; //s -> sim / n-> nao
}Estado;

typedef struct{
    int qtd_simbolos;
    char simbolo[8];

}Alfabeto;

typedef struct{
    Estado origem;
    char simbolo;
    Estado destino;
}Transicao;

typedef struct{
    Estado estados;
    Estado inicial;
    int qtd_estado;
    Alfabeto alfabeto;
    Transicao transicao;
}AFD;



