//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   Alunos: João Paulo de Souza                                                                            //                          //
//           Marco Túlio Nogueira Cambraia                                                                  //                                  //
//                                                                                                          //
//   Trabalho de Matemática Computacional                                                                   //                                   //
//                                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "file.h"
#include "gauss_pivoting.h"
#include "interpolation.h"
#include "trapezium_rule.h"
#include "horner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
/*função para criar a matrix, recebe o tamanho da matriz por parâmetro*/
double** create_matrix(int size){
    /*aloca dinamicamente espaço para a matriz*/
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++){ //percorre as linhas do vetor, para alocar as colunas
       matrix[i] = (double*) malloc(size * sizeof(double)); 
    }
    /*e assim que criada a matriz, retorna os ponteiros para ela*/
    return(matrix);
}
/*função para alocar espaço para o vetor de valores independentes*/
double* create_vector(int size){
    /*aloca dinamicamente tamanho para o vetor*/
    double* vector = (double*)malloc(size*sizeof(double));
    /*e retorna o ponteiro alocado*/
    return(vector);
}
/*função principal*/
int main(int argc, char *argv[]){

    /*teste do algoritmo de eliminação*/
    double** mat = create_matrix(4);
    double* vet = create_vector(4);
    mat[0][0] = 1;
    mat[0][1] = 6;
    mat[0][2] = 2;
    mat[0][3] = 4;
    mat[1][0] = 3;
    mat[1][1] = 19;
    mat[1][2] = 4;
    mat[1][3] = 15;
    mat[2][0] = 1;
    mat[2][1] = 4;
    mat[2][2] = 8;
    mat[2][3] = -12;
    mat[3][0] = 5;
    mat[3][1] = 33;
    mat[3][2] = 9;
    mat[3][3] = 3;
    vet[0] = 8;
    vet[1] = 25;
    vet[2] = 18;
    vet[3] = 72;
    /******************************************/      
    /*strings para os caminhos de dados*/
    /*uma para o arquivo de entrada e outra para o arquivo de saida em r*/
    char string[100];
    char path_input_file[100];
    char path_output_file[100];
    /*inicia as strings com espaço em branco para futura verificação*/
    strcpy(path_input_file," ");
    strcpy(path_output_file," "); 
    /*salva esses caminhos nas strings*/
    /*verifica se os caminhos foram preenchidos, se sim permite a execução do código*/
    if(argv[1] != NULL && argv[2] != NULL && argc == 3){ 
        strcpy(path_input_file,argv[1]);
        strcpy(path_output_file,argv[2]);
        /*recebe os valores lidos do arquivo*/
        values v = read_file(path_input_file);
        /*cria a matriz de tamanho n*/
        double** matrix = create_matrix(v.n);
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
        double* vector = create_vector(v.n);
        /*for para preencher o vetor com os valores de y*/
        for(int i = 0 ; i < v.n; i++){
            vector[i] = v.y[i];
        }
        /*agora realiza a eliminação de gauss com pivoteamento para
        encontrar o vetor x para o sistema contido na matriz*/
        double* x = gauss_pivoting_elimation(matrix,vector,v.n);
        /*agora será feita a interpolação desses valores encontrador para encontrar um função
        que passa pelos mesmos pontos que a anterior*/
        /*x, é o vetor de coefiencientes encontrado pela eliminação de gauss*/
        /*v.p é o vetor de pontos a serem interpolados*/
        /*v.i é a quantidade de pontos a serem interpolados*/
        /*e v.n - 1, sempre será o maior expoente da função*/
        double* y = interpolation(x,v.p,v.i,v.n);
        /*v.a é o intervalo a de integração*/
        /*v.b é o intervalo b de integração*/
        /*v.t é a quantidade de trapezios*/
        /*x é os coeficientes da função*/
        /*v.n - 1 é o expoente maior da função*/
        double area = trapezium_rule(v.a,v.b,v.t,x,v.n);
        data_out(path_output_file,v,x,y,area);
        /*executa o comando em R, para rodar o arquivo*/
        strcpy(string,"Rscript ");
        strcat(string,path_output_file);
        printf("%s\n",string);
        system(string);
        /*abrindo a imagem*/
        system("display saida.png");
    }
    /*erro no formato de iniciação do software*/
    else{
        printf("Formato errado de iniciação do software, são necessários os nomes/caminhos dos arquivos de entrada e saida!\n");
    }
    return(0);
}