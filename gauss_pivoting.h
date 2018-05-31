#ifndef GAUSS_PIVOTING_H
#define GAUSS_PIVOTING_H
/*funções relacionadas a matriz e o vetor de termos independentes, necessários para a resolução 
do sistema linear, pelo método de eliminação de gauss, implementando a outra parte do requisito 4 - Determinação 
do Polinômio Interpolador e requisito 5, Resolver U x = d por Gauss Pivotal */
/*função para mostrar os valores do vetor*/
void show_vector(double*vector,int size);
/*função para mostrar os valores na matriz*/
void show_matrix(double** matrix,int size);
/*função para realizar a troca de linhas da matriz*/
/*recebe os ponteiros dos vetores,ou linhas da matriz a serem trocados*/
void switch_lines(double*line_one,double*line_two,int size);
/*função para trocar a posição de termos independentes*/
/*recebe os ponteiros por referência dos dois valores a serem trocados*/
void switch_independent_terms(double *term_one,double*term_two);
/*função para realizar para encontrar os valores de x, de acordo com a matriz A e o vetor B
através da eliminação de Gauss com pivotiamento parcial*/
/*recebe o ponteiro da matriz, do vetor de termos independentes e o tamanho único, já
que são esperadas matrizes quadradas na função*/
double* gauss_pivoting_elimation(double**matrix,double*vector,int size);
/*no final espera-se retornar um vetor com os valores que resolvem o sistema linear*/

#endif