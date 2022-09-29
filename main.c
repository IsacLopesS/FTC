#include <stdio.h>
#include "lib.h"

void LerAFD(){
    FILE *arq;
    int result;
    char Str[50];

    arq = fopen("tese.txt", "rt");

    if (arq == NULL)
    {
        printf("Problemas na CRIACAO do arquivo\n");
        return;
    }
}

void main()
{
  FILE *arq;
  char Linha[100];
  char *result;
  int i;
  // Abre um arquivo TEXTO para LEITURA
  arq = fopen("test.txt", "rt");
  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");
     printf('hello');
     return;
  }
  i = 1;
  while (!feof(arq))
  {
	// Lê uma linha (inclusive com o '\n')
      result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
      if (result)  // Se foi possível ler
	  printf("Linha %d : %s",i,Linha);
      i++;
  }
  fclose(arq);
}