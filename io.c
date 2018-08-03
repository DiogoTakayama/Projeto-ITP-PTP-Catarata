#include <stdio.h>
#include <stdlib.h>

#include "config.h"

//Carrega as imagens na estruturas para que possa ser usadas para as op��es desejadas.
Pixel** carregar_imagem(int* lin, int* col, char* arq){
    FILE* arquivo;
    int cor, i, j;
    Pixel** imagem;

    
    arquivo = fopen(arq, "r"); // "r" indica que a imagem seja aberta em modo leitura

    //Teste afim de verificar se existe tal imagem passada por parametro.
    if(arquivo == NULL){
        printf("%s\n", arq);
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(arquivo, "%*[^\n]\n"); // Ao ler a imagem ele n�o pega nenhuma informa�ao da primeira linha

    fscanf(arquivo, "%d %d %d", col, lin, &cor); //Nessa parte ele pega a parte do cabe�alho da imagem.
    
    imagem = malloc((*lin) * sizeof(Pixel*) ); //Aloca dinamicamente as linhas da matriz.

    for(i=0; i<*lin; i++) 
        imagem[i] = malloc((*col) * sizeof(Pixel) ); //Aloca dinamicamente as locunas.

   //Lendo imagem
    for(i=0; i<*lin; i++)
        for(j=0; j<*col; j++)
            fscanf(arquivo, "%d %d %d", &imagem[i][j].R, &imagem[i][j].G, &imagem[i][j].B);
            //Neste momento est� coletando as informa��es da imagem e colocando na estrutura.
    
    fclose(arquivo);
    //Retorna o �ponteiro com a matriz alocada! Por enquanto esse dado s� existe dentro dessa fun��o, se esquecermos de retornar, essa matriz vai ficar perdida na mem�ria e a gente sem ela pra usar :~~~~
    return imagem;
}

//Cria uma nova imagem.
void cria_imagem(Pixel** img, int linha, int coluna, char* arq){
    FILE* arquivo;
    int i, j;

    arquivo = fopen(arq, "w"); //"w" Ordem de escrita, e caso n�o exista o arquivo ele o cria.

    //Testa pra ver se deu certo
    if(arquivo == NULL){
        printf("N�o � poss�vel escrever!\n"); //Caso o usuario n�o tenha permiss�o para escrever na pasta.
        exit(1);
    }

    // Colocando o cabe�alho da nova imagem. 
    fprintf(arquivo, "P3\n"); // P3 Formato da imagem PPM.
    fprintf(arquivo, "%d %d\n", coluna, linha);
    fprintf(arquivo, "255\n");

   
    for(i=0; i<linha; i++)
        for(j=0; j<coluna; j++)
            fprintf(arquivo, "%d %d %d\n", img[i][j].R, img[i][j].G, img[i][j].B);
                //Pegando as informa��es que est�o gravadas nas estruturas e colocando no novo arquivo.
}
