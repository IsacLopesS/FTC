#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int info;
	struct node* next;
} No;

typedef struct pilha {
	No *topo;
} Pilha;

Pilha* create_stack (void);
void push(Pilha *p, double elem);
int pop();
int empty (Pilha *p);
void print (Pilha *p);
void free_stack (Pilha *p);