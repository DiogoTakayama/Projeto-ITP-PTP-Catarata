#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "config.h"

#define PI 3.14159265

Pixel** alocarImagem(int lin, int col){
    int i;
    Pixel** nova;

    nova = malloc(sizeof(Pixel*) * lin);

    if(nova == NULL){
        printf("Erro ao alocar a memoria\n");
        exit(1);
    }

    for(i=0; i<lin; i++){ 
        nova[i] = malloc(sizeof(Pixel) * col);

        if(nova[i] == NULL){
            printf("Erro ao alocar a memoria\n");
            exit(1);
        }
    }

    return nova;
}

//Função para fazer a transformação para tons de cinza
Pixel** escalaCinza(Pixel** img, int linhas, int colunas){
    //i e j controlam o laço
    //media guarda o valor do cálculo do tom de cinza do pixel
    int i, j;
    int media;
    Pixel** nova;

    nova = alocarImagem(linhas, colunas);

    //Para cada pixel da imagem...
    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            //...calcula o tom de cinza da imagem de acordo com a fórmula do projeto
            // 30% do vermelho, 59% do Verde, 11% de Azul
            media = 0.3*img[i][j].R + 0.59*img[i][j].G + 0.11*img[i][j].B;

            //Repete o valor calculado para os três componentes, para ficar cinza
            nova[i][j].R = nova[i][j].G = nova[i][j].B = media;
        }
    }

    return nova;
}

Pixel** convolucaoMatrizes(Pixel** img, int alt, int larg, int lin, int col, int kernel[][col], int offset){
    int i, j, k, l;
    int offLinha, offColuna;
    Pixel valor;
    Pixel** nova;

    nova = alocarImagem(alt, larg);

    //Para cada pixel da imagem...
    for(i=0; i<alt; i++){
        for(j=0; j<larg; j++){
            //..vamos calcular o valor do pixel i,j a partir dos valores dos seus vizinhos
            //Inicialmente, vamos zerar os valores
            valor.R = valor.G = valor.B = 0;

            //Para cada posição do filtro
            //Vamos ajustar a área de verificação da imagem original a partir do tamanho do filtro (lin, col)
            //Como o pixel i,j será centralizado na matriz do filtro, vamos verificar um deslocamento de -lin/2 (metade do filtro) ate lin/2, e a mesma coisa para as colunas
            for(k=0, offLinha=-lin/2; k<lin; k++, offLinha++){
                for(l=0, offColuna=-col/2; l<col; l++, offColuna++){
                    //Verifica se o pixel está na borda, se estiver não faz nada
                    if(i+offLinha >= 0 && i+offLinha < alt && j+offColuna >= 0 && j+offColuna < larg){
                        //O valor, para cada componente de cor, ser o acúmulo da multiplicação entre valores de posições correspondentes na matriz da imagem e na matriz do filtro
                        valor.R += (img[i+offLinha][j+offColuna].R * kernel[k][l])/offset;
                        valor.G += (img[i+offLinha][j+offColuna].G * kernel[k][l])/offset;
                        valor.B += (img[i+offLinha][j+offColuna].B * kernel[k][l])/offset;
                    }
                }
            }

            //Quando termina de calcular o novo valor para o Pixel valor, atualiza a imagem original
            nova[i][j] = valor;
        }
    }

    return nova;
}

//Função que aplica um filtro Gaussiano para borrar a imagem
Pixel** filtroGaussiano(Pixel** img, int lin, int col){
    //Filtro Gaussiano sugerido no projeto
    int filtro[5][5] = {{2, 4, 5, 4, 2},
                        {4, 9, 12, 9, 4},
                        {5, 12, 15, 12, 5},
                        {4, 9, 12, 9, 4},
                        {2, 4, 5, 4, 2}};

    Pixel** nova;

    //Chama a convolução da imagem com o filtro
    nova = convolucaoMatrizes(img, lin, col, 5, 5, filtro, 159);

    return nova;
}

//Filtro do Sobel
Pixel** filtroSobel(Pixel** img, int lin, int col, int direcoes[lin][col]){
    int filtro_H[3][3] =    {{1, 2, 1},
                             {0, 0, 0},
                             {-1, -2, -1}};

    int filtro_V[3][3] =    {{1, 0, -1},
                             {2, 0, -2},
                             {1, 0, -1}};

    Pixel** horizontal;
    Pixel** vertical;
    Pixel** nova;
    int i, j;
    double angulo;

    
    horizontal = convolucaoMatrizes(img, lin, col, 3, 3, filtro_H, 1);
    vertical = convolucaoMatrizes(img, lin, col, 3, 3, filtro_V, 1);

    nova = alocarImagem(lin, col);

    for(i=0; i<lin; i++){
        for(j=0; j<col; j++){
            nova[i][j].R = sqrt(horizontal[i][j].R*horizontal[i][j].R + vertical[i][j].R*vertical[i][j].R);
            nova[i][j].G = sqrt(horizontal[i][j].G*horizontal[i][j].G + vertical[i][j].G*vertical[i][j].G);
            nova[i][j].B = sqrt(horizontal[i][j].B*horizontal[i][j].B + vertical[i][j].B*vertical[i][j].B);

            angulo = atan2(vertical[i][j].R, horizontal[i][j].R)*180.0/PI;

            if((angulo >= 0.0 && angulo < 22.5) || (angulo >= 157.5 && angulo < 180.0))
                direcoes[i][j] = 0;
            else if(angulo >= 22.5 && angulo < 67.5)
                direcoes[i][j] = 1;
            else if(angulo >= 67.5 && angulo < 112.5)
                direcoes[i][j] = 2;
            else
                direcoes[i][j] = 3;
        }
    }

    return nova;
}
//Função que realça as arestas.
Pixel** realceAresta(Pixel** img, int lin, int col){
    int direcoes[lin][col];
    Pixel** nova;
    int i, j;

    nova = filtroSobel(img, lin, col, direcoes);

    for(i=0; i<lin; i++){
        for(j=0; j<col; j++){
            switch(direcoes[i][j]){
                case 0:
                    if(j-1 >= 0 && j+1 < col){
                        if(nova[i][j].R < nova[i][j-1].R || nova[i][j].R < nova[i][j+1].R)
                            nova[i][j].R = nova[i][j].G = nova[i][j].B = 0;
                    }
                    break;
                case 1:
                    if(i+1 < lin && j-1 >= 0 && i-1 >= 0 && j+1 < col){
                        if(nova[i][j].R < nova[i+1][j-1].R || nova[i][j].R < nova[i-1][j+1].R)
                            nova[i][j].R = nova[i][j].G = nova[i][j].B = 0;
                    }
                    break;
                case 2:
                    if(i-1 >= 0 && i+1 < lin){
                        if(nova[i][j].R < nova[i-1][j].R || nova[i][j].R < nova[i+1][j].R)
                            nova[i][j].R = nova[i][j].G = nova[i][j].B = 0;
                    }
                    break;
                case 3:
                    if(i-1 >= 0 && j-1 >= 0 && i+1 < lin && j+1 < col){
                        if(nova[i][j].R < nova[i-1][j-1].R || nova[i][j].R < nova[i+1][j+1].R)
                            nova[i][j].R = nova[i][j].G = nova[i][j].B = 0;
                    }
                    break;
            }

            if(nova[i][j].R >= 75)
                nova[i][j].R = nova[i][j].G = nova[i][j].B = 255;
            else if (nova[i][j].R < 50)
                nova[i][j].R = nova[i][j].G = nova[i][j].B = 0;
            else
                nova[i][j].R = nova[i][j].G = nova[i][j].B = 100;
        }
    }

    return nova;
}