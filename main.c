//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Alunos: João Paulo de Souza                                                                            //                          //
//           Marco Túlio Nogueira Cambraia                                                                  //                                  //
//                                                                                                          //
//   Trabalho de Matemática Computacional                                                                   //                                   //
//                                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "file.h"
#include "gauss_pivoting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*função para criar a matrix, recebe o tamanho da matriz por parâmetro*/
float** create_matrix(int size){
    /*aloca dinamicamente espaço para a matriz*/
    float** matrix = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++){ //percorre as linhas do vetor, para alocar as colunas
       matrix[i] = (float*) malloc(size * sizeof(float)); 
    }
    /*e assim que criada a matriz, retorna os ponteiros para ela*/
    return(matrix);
}
/*função para alocar espaço para o vetor de valores independentes*/
float* create_vector(int size){
    /*aloca dinamicamente tamanho para o vetor*/
    float* vector = (float*)malloc(size*sizeof(float));
    /*e retorna o ponteiro alocado*/
    return(vector);
}
/*função principal*/
int main(int argc, char *argv[]){
    /*strings para os caminhos de dados*/
    /*uma para o arquivo de entrada e outra para o arquivo de saida em r*/
    char path_input_file[100];
    char path_output_file[100]; 
    /*salva esses caminhos nas strings*/
    strcpy(path_input_file,argv[1]);
    //strcpy(path_output_file,argv[2]);
    /*recebe os valores lidos do arquivo*/
    values v = read_file(path_input_file);
    /*cria a matriz de tamanho n*/
    float** matrix = create_matrix(v.n);
    /*preenche a matrix para realizar a interpolação dos valores, que são os valores de x*/
    /*for externo para as linhas*/
    for(int i  = (v.n - 1); i >= 0; i--){
        /*e for interno para as colunas*/
        for(int j = (v.n - 1); j >= 0; j--){
            /*matriz recebe o valor de x, elevado a sua coluna, iniciando da maior para a menor*/
            matrix[i][j] = pow(v.x[i],j);
        }
    }
    /*cria agora o vetor de termos independentes ou seja os valores de y*/
    float* vector = create_vector(v.n);
    /*for para preencher o vetor com os valores de y*/
    for(int i = 0 ; i < v.n; i++){
        vector[i] = v.y[i];
    }
    /*agora precisado fazer a eliminação de gauss pivotal */
    gauss_pivoting_elimation(matrix,vector);
    return(0);
}