#ifndef FILE_H
#define FILE_H
#include <stdbool.h>
/*Estrutura necessário para recebimento dos dados do arquivo para uso no software*/
typedef struct VALUES{
    int n;//Números de pontos tabelados para x e y
    double* x;
    double* y;
    double a;//intervalos da integral a e b
    double b;
    int i;//números de pontos a sofrerem interpolação p
    double* p;
    int t;//quantidade de trapezios
    bool verify[8];
}values;
/*Função para ler o arquivo passado por parâmetro e devolve os dados para ser usados no arquivo
 principal do software, implementando o requisito 1 - Entrada de Dados*/
/*recebe por parametro o caminho do arquivo a ser lido*/
values read_file(char readfile[]);
/* espera-se retornar a estrutura com os valores preenchidos pelos dados do arquivo*/

/*função para montar o arquivo de saida em R, recebe por paramêtro o 
caminho de saída, a struct de valores lidos, o vetor resultante da eliminação de 
gauss, as imagens da função interpolada e a área dos trapézios, que é a integral
da função, implementando o requisito 3 - Saída de Dados (Script)*/
void data_out(char path_out[100],values v,double *x,double *y,double area);
 /*como saída, espera-se que um arquivo script em R tenha sido criado com os dados encontrados pelas outras
partes do trabalho*/
#endif