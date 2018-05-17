#ifndef FILE_H
#define FILE_H

/*estrutura que será preenchidas com os dados do arquivo*/
typedef struct VALUES{
    int n;//Números de pontos tabelados para x e y
    float* x;
    float* y;
    int a;//intervalos da integral a e b
    int b;
    int i;//números de pontos a sofrerem interpolação p
    float* p;
    int t;//quantidade de trapezios
}values;
/*função para ler o arquivo e retornar um vetor com os valores necessários*/
values read_file(char readfile[]);

#endif