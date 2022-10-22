#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.c"
#define tamNome 20
typedef struct
{
    char nomeEstado[tamNome];
    int inicial; //1 para sim, 0 para nao
    int final;   //1 para sim, 0 para nao
    int id;
    int chegou; // 1 para sim, 0 para nao
} Estado;
typedef struct
{
    char elementoAlfabeto;
} Alfabeto;
typedef struct
{
    Estado *origem;
    Alfabeto *consumo;
    Estado *destino;
} transicao;
typedef struct
{
    Estado *estados;
    Alfabeto *alfabeto;
    transicao *transicoes;
    int qtdEstados;
    int tamAlfabeto;
    int qtdTransicoes;
    int qtdFinais;
} AFD;

void memoriaInsuficiente()
{
    printf("\n\nMEMÓRIA DISPONÍVEL INSUFICIENTE\n\n");
    exit(2);
}

char *stringFinais(AFD afd)
{
    char *str;
    str = (char *)malloc(tamNome * afd.qtdFinais * sizeof(char));
    if (str == NULL)
        memoriaInsuficiente();
    for (int i = 0; i < afd.qtdEstados; i++)
        if (afd.estados[i].final == 1)
        {
            strcat(str, afd.estados[i].nomeEstado); //strcat concatena
            strcat(str, " ");
        }
    return str;
}

void lerafd(AFD *afd, char *nome)
{
    char linha[200];
    int indice = 0;
    FILE *fp = fopen(nome, "r");
    if (fp == NULL)
    {
        printf("\n\nARQUIVO DE TEXTO CONTENDO O AFD É INVÁLIDO\n\n");
        exit(1);
    }
    char ch = getc(fp);
    //Lê os estados e armazena em estruturas
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp); //getc pega um caracter
    }
    linha[indice] = '\0';
    afd->qtdEstados = atoi(linha);
    ch = getc(fp);
    afd->estados = (Estado *)malloc(afd->qtdEstados * sizeof(Estado));
    if (afd->estados == NULL)
        memoriaInsuficiente();
    for (int i = 0; i < afd->qtdEstados; i++)
    {
        indice = 0;
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[++indice] = '\0';
        indice = 0;
        ch = getc(fp);
        strcpy(afd->estados[i].nomeEstado, linha);
    }

    //Lê o alfabeto e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    afd->tamAlfabeto = atoi(linha);
    afd->alfabeto = (Alfabeto *)malloc(afd->tamAlfabeto * sizeof(Alfabeto));
    if (afd->alfabeto == NULL)
        memoriaInsuficiente();
    for (int i = 0; i < afd->tamAlfabeto; i++)
    {
        afd->alfabeto[i].elementoAlfabeto = getc(fp);
        ch = getc(fp);
    }
    ch = getc(fp);

    //Lê transicoes e armazena nas estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    afd->qtdTransicoes = atoi(linha);
    afd->transicoes = (transicao *)malloc(afd->qtdTransicoes * sizeof(transicao));
    if (afd->transicoes == NULL)
        memoriaInsuficiente();
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < afd->qtdTransicoes; i++)
    {
        //Lê a linha inteira
        indice = 0;
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        ch = getc(fp);

        //Particiona
        int j = 0;
        int k = 0;
        char aux[20];

        while (linha[j] != ' ')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < afd->qtdEstados; a++)
            if (strcmp(afd->estados[a].nomeEstado, aux) == 0)
                afd->transicoes[i].origem = &afd->estados[a];
        j++;
        k = 0;

        while (linha[j] != ' ')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < afd->tamAlfabeto; a++)
            if (afd->alfabeto[a].elementoAlfabeto == aux[0])
                afd->transicoes[i].consumo = &afd->alfabeto[a];
        j++;
        k = 0;

        while (linha[j] != '\0')
            aux[k++] = linha[j++];
        aux[k] = '\0';
        for (int a = 0; a < afd->qtdEstados; a++)
            if (strcmp(afd->estados[a].nomeEstado, aux) == 0)
                afd->transicoes[i].destino = &afd->estados[a];
    }

    // atribuir id para os estados
    for (int i = 1; i <= afd->qtdEstados; i++)
    {
        afd->estados[i].id = i;
    }

    //Lê o estado inicial e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    ch = getc(fp);
    for (int i = 0; i < afd->qtdEstados; i++)
    {
        if (strcmp(afd->estados[i].nomeEstado, linha) == 0)
            afd->estados[i].inicial = 1;
        else
            afd->estados[i].inicial = 0;
    }
    //Lê os estados finais e armaneza em estruturas
    indice = 0;
    while (ch != '\n')
    {
        linha[indice++] = ch;
        ch = getc(fp);
    }
    linha[indice] = '\0';
    afd->qtdFinais = atoi(linha);
    indice = 0;
    ch = getc(fp);
    for (int i = 0; i < afd->qtdEstados; i++)
        afd->estados[i].final = 0;
    for (int i = 0; i < afd->qtdFinais; i++)
    {
        while (ch != '\n')
        {
            linha[indice++] = ch;
            ch = getc(fp);
        }
        linha[indice] = '\0';
        for (int i = 0; i < afd->qtdEstados; i++)
            if (strcmp(afd->estados[i].nomeEstado, linha) == 0)
                afd->estados[i].final = 1;
        indice = 0;
        ch = getc(fp);
    }
    fclose(fp);
}

void escreveDot(char nome[], AFD afd)
{
    char *str = stringFinais(afd);
    FILE *arq = fopen(nome, "wt");
    if (arq == NULL)
    {
        printf("\n\nNÃO FOI POSSÍVEL CRIAR ARQUIVO .dot\n\n");
        exit(3);
    }
    fprintf(arq, "digraph finite_state_machine {\n"
                 "\trankdir=LR;\n\tsize=\"10\"\n\n"
                 "\tnode [shape = doublecircle]; %s;",
            str);
    fprintf(arq, "\n\tnode [shape = point]; qi;\n");
    //funçao que escreve valores finais
    fprintf(arq, "\n\tnode [shape = circle]");
    for (int i = 0; i < afd.qtdEstados; i++)
        if (afd.estados[i].inicial == 1)
            fprintf(arq, "\n\tqi -> %s;", afd.estados[i].nomeEstado);

    for (int i = 0; i < afd.qtdTransicoes; i++)
        fprintf(arq, "\n\t%s -> %s [label = %c ];", afd.transicoes[i].origem, afd.transicoes[i].destino, afd.transicoes[i].consumo->elementoAlfabeto);
    fprintf(arq, "\n\t}");
    free(str);
    fclose(arq);
}

void escreveTxt(AFD afd, char *nome)
{
    FILE *arq = fopen(nome, "wt");
    if (arq == NULL)
    {
        printf("\n\nNÃO FOI POSSÍVEL CRIAR ARQUIVO .txt");
        exit(4);
    }
    fprintf(arq, "%d\n", afd.qtdEstados);
    for (int i = 0; i < afd.qtdEstados; i++)
        fprintf(arq, "%s\n", afd.estados[i].nomeEstado);
    fprintf(arq, "%d\n", afd.tamAlfabeto);
    for (int i = 0; i < afd.tamAlfabeto; i++)
        fprintf(arq, "%c\n", afd.alfabeto[i].elementoAlfabeto);
    fprintf(arq, "%d\n", afd.qtdTransicoes);
    for (int i = 0; i < afd.qtdTransicoes; i++)
        fprintf(arq, "%s %c %s\n", afd.transicoes[i].origem, afd.transicoes[i].consumo->elementoAlfabeto, afd.transicoes[i].destino);
    for (int i = 0; i < afd.qtdEstados; i++)
        if (afd.estados[i].inicial == 1)
            fprintf(arq, "%s\n", afd.estados[i].nomeEstado);
    fprintf(arq, "%d\n", afd.qtdFinais);
    for (int i = 0; i < afd.qtdEstados; i++)
        if (afd.estados[i].final == 1)
            fprintf(arq, "%s\n", afd.estados[i].nomeEstado);
    fclose(arq);
}

char reconhecePalavra(AFD afd, char *input, int tam, Estado *estado_atual)
{
    if (tam != 0)
    {
        for (int i = 0; i < afd.qtdTransicoes; i++)
            if (afd.transicoes[i].origem == estado_atual && afd.transicoes[i].consumo->elementoAlfabeto == *input)
                return reconhecePalavra(afd, input + 1, tam - 1, afd.transicoes[i].destino);
        return '0';
    }
    else
    {
        if (estado_atual->final == 1)
            return '1';
        else
            return '0';
    }
}

void complemento(AFD *afd)
{
    int cont = 0;
    
    for (int i = 0; i < afd->qtdEstados; i++)
        (afd->estados[i].final == 1) ? (afd->estados[i].final = 0) : (afd->estados[i].final = 1);

    cont = afd->qtdEstados - afd->qtdFinais;
    afd->qtdFinais = cont;
}

void reconheceEscreveArquivo(char *palavras, char *saida, AFD afd)
{

    //Abertura de arquivos para leitura das palavras e saída de resultados
    FILE *arq = fopen(palavras, "rt");
    FILE *resultados = fopen(saida, "wt");

    if (arq == NULL)
    {
        printf("\n\nERRO AO ABRIR ARQUIVO COM AS PALAVRAS\n\n");
        exit(5);
    }
    char ch = fgetc(arq);
    char *strAux;
    int i;
    while (ch != EOF)
    {
        char *str = (char *)malloc(sizeof(char));
        if (str == NULL)
            memoriaInsuficiente();
        str[0] = ch;
        for (i = 1; ch != '\n' && ch != EOF; i++)
        {
            strAux = str;
            str = (char *)malloc((i + 1) * sizeof(char));
            if (str == NULL)
                memoriaInsuficiente();
            for (int j = 0; j < i; j++)
                str[j] = strAux[j];
            ch = fgetc(arq);
            str[i] = ch;
            free(strAux);
        }
        if (ch != EOF)
            ch = fgetc(arq);
        fprintf(resultados, "%c\n", reconhecePalavra(afd, str, i - 1, &afd.estados[0]));
        free(str);
    }
    fclose(arq);
    fclose(resultados);
}
void multiplicaAfd(AFD afd, AFD afd2)
{

printf('\n\nisac aqui ->  %d',afd.qtdTransicoes);
exit(10);

}

void minimizacao(AFD *afd)
{
    Estado proximoEstadoZero, proximoEstadoUm;
    Pilha *faltaChecar = create_stack();
    AFD teste;
    
    //coloca no estado inicial
    int id_atual;
    for (int i = 0; i < afd->qtdEstados; i++) {
        if (afd->estados[i].inicial == 1) {
            afd->estados[i].chegou = 1;
            push(faltaChecar, afd->estados[i].id);
        }
    }

    //varifica os estados inalcançáveis
    do {        
        int indexTrasacao = 0, contador = 0;
        id_atual = pop(faltaChecar);

        while(contador < afd->tamAlfabeto) {
            if (afd->transicoes[indexTrasacao].origem->nomeEstado == afd->estados[id_atual].nomeEstado) {
                if (afd->transicoes[indexTrasacao].destino->chegou == 0) {
                    afd->transicoes[indexTrasacao].destino->chegou = 1;
                    push(faltaChecar, afd->transicoes[indexTrasacao].destino->id); 
                }
                contador++;
            }
            indexTrasacao++;
        }
    } while (empty(faltaChecar) == 0);
    
    // retirar estados inalcançáveis
    for (int index = 0; index < afd->qtdEstados; index++) {
        if(afd->estados[index].chegou == 0 ) {
            
            for (int indexRetirarTransacao = 0; indexRetirarTransacao <= afd->qtdTransicoes; indexRetirarTransacao++) {
                if (afd->transicoes[indexRetirarTransacao].origem->id == afd->estados[index].id) {

                    for (int indexRetirarTransacao2 = indexRetirarTransacao; indexRetirarTransacao < afd->qtdTransicoes - 1; indexRetirarTransacao++) {
                        afd->transicoes[indexRetirarTransacao2] = afd->transicoes[indexRetirarTransacao2 + 1];
                    }

                    afd->qtdTransicoes = afd->qtdTransicoes - 1;
                    indexRetirarTransacao = indexRetirarTransacao - 1;
                }
            }

            for (int indexRetirar = index; indexRetirar < afd->qtdEstados; indexRetirar++) {
                afd->estados[indexRetirar] = afd->estados[indexRetirar + 1];
            }
            afd->qtdEstados = afd->qtdEstados - 1;
        }
    }

    //varifica estados equivalentes
    
    for (int i = 0; i < afd->qtdEstados; i++) 
    {   
        if (afd->estados[i].chegou == 1) 
        {
            for (int j = 0; j <= afd->qtdEstados; j++) 
            {
                int iguais = 0;
                int trasacaoI = 0;
                int transacaoJ = 0;
                Pilha *trasacaoEliminar = create_stack();

                if (i != j) {
                    if (afd->estados[j].chegou == 1) 
                    {
                        int contadorI = 0;
                        while (contadorI < afd->tamAlfabeto) 
                        {
                            if (afd->estados[i].id == afd->transicoes[trasacaoI].origem->id ) {
                                int contadorJ = 0;
                                transacaoJ = 0;
                                
                                while (contadorJ < afd->tamAlfabeto)
                                {
                                    if (afd->estados[j].id == afd->transicoes[transacaoJ].origem->id) {

                                        if (afd->transicoes[transacaoJ].consumo->elementoAlfabeto == afd->transicoes[trasacaoI].consumo->elementoAlfabeto) {

                                            if (afd->transicoes[transacaoJ].destino->final == afd->transicoes[trasacaoI].destino->final) {

                                                if (afd->transicoes[transacaoJ].origem->final == afd->transicoes[trasacaoI].origem->final) {
                                                    iguais++;
                                                    push(trasacaoEliminar, transacaoJ);
                                                }
                                            }
                                        }
                                        contadorJ++;
                                    }
                                    transacaoJ++;
                                }
                                
                                contadorI++;
                            }
                            
                            trasacaoI++;
                        }
                    }
                }

                if (iguais == afd->tamAlfabeto) {               
                    while (empty(trasacaoEliminar) == 0)
                    {
                        int idTrasacao = pop(trasacaoEliminar);

                        for (int indexRetirarTransacao = idTrasacao; indexRetirarTransacao < afd->qtdTransicoes; indexRetirarTransacao++) {
                            afd->transicoes[indexRetirarTransacao] = afd->transicoes[indexRetirarTransacao + 1];
                        }

                        afd->qtdTransicoes = afd->qtdTransicoes - 1;
                    }

                    for (int indexRetirarTransacao = 0; indexRetirarTransacao < afd->qtdTransicoes; indexRetirarTransacao++) {
                        if (afd->transicoes[indexRetirarTransacao].destino->id == afd->estados[j].id) {
                            afd->transicoes[indexRetirarTransacao].destino = &afd->estados[i];
                        }
                    }


                    if (afd->estados[j].final == 1) {
                        afd->qtdFinais = afd->qtdFinais - 1;
                    }

                    for (int index = j; index <= afd->qtdEstados; index++) {
                        if (index < afd->qtdEstados) {
                            afd->estados[index] = afd->estados[index+1];
                            for (int indexRetirarTransacao = 0; indexRetirarTransacao < afd->qtdTransicoes; indexRetirarTransacao++) {
                                if (afd->transicoes[indexRetirarTransacao].origem->id == afd->estados[index + 1].id) {
                                    afd->transicoes[indexRetirarTransacao].origem = &afd->estados[index];
                                }
                                if (afd->transicoes[indexRetirarTransacao].destino->id == afd->estados[index + 1].id) {
                                    afd->transicoes[indexRetirarTransacao].destino = &afd->estados[index];
                                }
                            }
                        } 
                    }
                    
                    afd->qtdEstados = afd->qtdEstados - 1;
                }
            }
        }
    }

}

