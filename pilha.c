#include "pilha.h"

Pilha* create_stack (void) {
	Pilha *p = (Pilha*)malloc(sizeof(Pilha));
	p->topo = NULL;
	return p;
}

void push
(Pilha *p, double elem) {
	No *n = (No*)malloc(sizeof(No));
	n->info = elem;
	n->next = p->topo;
	p->topo = n;
}

int pop(Pilha *p){
	if(empty(p)) { exit(1); }
	No *n = p->topo;
	int elem = n->info;
	p->topo = n->next;
	free(n);
	return elem;
}

int empty (Pilha *p) {
	return (p->topo == NULL);
}

void print (Pilha *p) {
	No *n;
	for (n=p->topo; n!=NULL; n=n->next) {
		printf("%d\n", n->info);
	}
}

void free_stack (Pilha *p) {
	No *n = p->topo;
	while (n != NULL) {
		No *temp = n->next;
		free(n); /*desalocando os nos*/
		n = temp;
	}
	free (p); /*desalocando a pilha*/
}