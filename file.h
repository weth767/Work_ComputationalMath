#ifndef FILE_H
#define FILE_H

/*estrutura que será preenchidas com os dados do arquivo*/
typedef struct VALUES{
    int n;//Números de pontos tabelados para x e y
    double* x;
    double* y;
    double a;//intervalos da integral a e b
    double b;
    int i;//números de pontos a sofrerem interpolação p
    double* p;
    int t;//quantidade de trapezios
}values;
/*função para ler o arquivo e retornar um vetor com os valores necessários*/
values read_file(char readfile[]);
void data_out(char path_out[100],values v,double *x,double *y,double area);
#endif