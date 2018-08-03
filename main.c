#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "io.h"
#include "operacoes.h"

int main(int argc, char* argv[]){
    // Esse parte dos ponteiros para ponteiros guarda as imagens forma de matrizes.
    Pixel** imagem;
    Pixel** cinza;
    Pixel** gauss;
    Pixel** sobel;
    Pixel** recebeSobel;

    int linhas=0, colunas=0; //
    int opc;

    imagem = carregar_imagem(&linhas, &colunas, argv[2]); 

 while(opc != 5){

    printf("\n\t\t\tSistema Detecoes de Catarata IMD\n");
        printf( "_____________________________________________________________________________\n" );
        printf( "\n\t\t\tMENU PRINCIPAL\n\n" );
        printf( "-----------------------------------------------------------------------------\n" );
        printf(" Escolha uma das seguintes opcoes:\n\n");
        printf("  1.Criar uma nova imagem\n");
        printf("  2.escala Cinza\n");
        printf("  3.filtro Gaussiano\n");
        printf("  4.filtrar com Sobel\n");
        printf( "-----------------------------------------------------------------------------\n" );
        printf( "\t\t\t\t5 - Sair\n" );
        printf( "_____________________________________________________________________________\n" );

    scanf("%d", &opc);
    system("clear");


    switch (opc){
    //Cria uma nova imagem com o nome de Novo.ppm
    	case 1:
    	cria_imagem(imagem, linhas, colunas, "Novo.ppm");
    	break;
    	case 2: 
    	cinza = escalaCinza(imagem, linhas, colunas);
	    cria_imagem(cinza, linhas, colunas, "Cinza.ppm");
	    break;
	    case 3:
	    cinza = escalaCinza(imagem, linhas, colunas);
	    gauss = filtroGaussiano(cinza, linhas, colunas);
	    cria_imagem(gauss, linhas, colunas, "Gauss.ppm");
	    break;
	    case 4:
	    cinza = escalaCinza(imagem, linhas, colunas);
	    gauss = filtroGaussiano(cinza, linhas, colunas);
	    recebeSobel = realceAresta(gauss, linhas, colunas);
    	cria_imagem(recebeSobel, linhas, colunas, "Arestas.ppm");
    	break;
    	case 5:		
		printf("Fechando programa\n");
		break;
    	default:
		printf("Comando desconhecido\n");

	}
}
  
    free(imagem);

    return 0;
}