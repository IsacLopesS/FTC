#include "operacoes.h"

void Decide(int argc, char *argv[], int n, AFD *afd, AFD *afd2)
{
    if (argc == 5 || argc == 6)
    {
        if ((strcmp(argv[n], "--complemento") == 0) && (strcmp(argv[n + 2], "--output") == 0))
        {
            lerafd(afd, argv[n + 1]);
            complemento(afd);
            escreveTxt(*afd, argv[n + 3]);
            return;
        }
        else if ((strcmp(argv[n], "--reconhecer") == 0) && (strcmp(argv[n + 3], "--output") == 0))
        {
            lerafd(afd, argv[n + 1]);
            reconheceEscreveArquivo(argv[n + 2], argv[n + 4], *afd);
            return;
        }
        else if ((strcmp(argv[n], "--dot") == 0) && (strcmp(argv[n + 2], "--output") == 0))
        {
            lerafd(afd, argv[n + 1]);
            escreveDot(argv[n + 3], *afd);
            return;
        }
        else if ((strcmp(argv[n], "--intersecao") == 0) && (strcmp(argv[n + 3], "--output") == 0))
        {
            lerafd(afd, argv[n + 1]);
            lerafd(afd2, argv[n + 2]);
            multiplicaAfd(*afd, *afd2);


        }
        else if ((strcmp(argv[n], "--uniao") == 0) && (strcmp(argv[n + 3], "--output") == 0))
        {

        }
        else if ((strcmp(argv[n], "--minimizacao") == 0) && (strcmp(argv[n + 2], "--output") == 0))
        {
            lerafd(afd, argv[n + 1]);
            minimizacao(afd);
            escreveTxt(*afd, argv[n + 3]);
            return;
        }

    }
    printf("\n\nATENÇÃO, O USO DEVE OCORRER DA SEGUINTES FORMAS:");
    printf("\n\n./afdtool --complemento {nome_arquivo_afd}.txt --output {nome_arquivo_saida}.txt");
    printf("\n./afdtool --reconhecer {nome_arquivo_afd}.txt {nome_arquivo_palavras}.txt --output {nome_arquivo_saida}.txt\n");  
    printf("\n\n./afdtool --intersecao {nome_arquivo_afd}.txt {nome_arquivo_afd}.txt --output {nome_arquivo_saida}.txt\n ");
    printf("\n\n./afdtool --uniao {nome_arquivo_afd}.txt {nome_arquivo_afd}.txt --output {nome_arquivo_saida}.txt\n ");
    printf("\n\n./afdtool --minimizacao {nome_arquivo_afd}.txt --output {nome_arquivo_saida}.txt\n ");
}
int main(int argc, char *argv[])
{
    AFD afd, afd2;
    Decide(argc, argv, 1, &afd, &afd2);
    
    return 0;
}
