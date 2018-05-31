#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*funções relacionadas a matriz e o vetor de termos independentes, necessários para a resolução 
do sistema linear, pelo método de eliminação de gauss, implementando a outra parte do requisito 4 - Determinação 
do Polinômio Interpolador e requisito 5, Resolver U x = d por Gauss Pivotal */
/*função para mostrar os valores na matriz*/
void show_matrix(double** matrix,int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("\t%lf ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
/*função para mostrar os valores do vetor*/
void show_vector(double*vector,int size){
    for(int i = 0; i < size; i++){
        printf("%lf ",vector[i]);
    }
    printf("\n");
}
/*função para realizar a troca de linhas da matriz*/
/*recebe os ponteiros dos vetores,ou linhas da matriz a serem trocados*/
void switch_lines(double*line_one,double*line_two,int size){
    /*vetor auxiliar para guardar uma das linhas*/
    double temp_line[size];
    /*clona uma das linhas nesse vetor*/
    for(int i = 0 ; i < size; i++){
        /*cada indice i, vai para posição igual no outro vetor*/
        temp_line[i] = line_one[i];
    }
    /*agora faz a primeira linha receber a segunda*/
    for(int j = 0; j < size; j++){
        line_one[j] = line_two[j];
    }
    /*e a segunda linha recebe a temporária*/
    for(int k = 0; k < size; k++){
        line_two[k] = temp_line[k];
    }
}
/*função para trocar a posição de termos independentes*/
/*recebe os ponteiros por referência dos dois valores a serem trocados*/
void switch_independent_terms(double *term_one,double*term_two){
    /*com uma variável auxiliar guarda o valor de um dos termos*/
    double temp_term = *term_one;
    /*e faz que um recebe o outro*/
    *term_one = *term_two;
    /*e o outro receba o temporário*/
    *term_two = temp_term;
}

/*função para realizar o método de resolução de sistemas lineares, chamada eliminação de gauss,
entretanto, um forma mais aprimorada do método que consiste em pivotear linhas para um melhor desempenho
do método*/
/*recebe o ponteiro da matriz, do vetor de termos independentes e o tamanho único, já
que são esperadas matrizes quadradas na função*/
double* gauss_pivoting_elimation(double**matrix,double*vector,int size){
    /*aloca espaço de memória para o vetor de x'termos*/
    /*que será devolvido no final da função*/
    double multiplier;
    double* x = (double*)malloc(size*sizeof(double));
    /*preenche o vetor x com zeros*/
    for(int i = 0; i < size; i++){
        x[i] = 0;
    }
    /*variavel index, que guardará o indice de troca caso seja necessária a troca*/
    int index;
    double bigger;
    /*laço de repetição externo, que caminha entre as colunas da matriz*/
    for(int pivot = 0; pivot < (size - 1); pivot++){
        /*zera o index a cada iteração do laço externo para controle de troca*/
        index = pivot;
        bigger = matrix[pivot][pivot];
        /*laço de repetição interno para as linhas da matriz*/
        for(int switch_line = pivot + 1; switch_line < size; switch_line++){
            /*verifica todas as posições abaixo da pivo na mesma coluna*/
            /*procurando um elemento maior, se encontrar*/
            if(fabs(matrix[switch_line][pivot]) > fabs(bigger)){
                /*guarda seu index*/
                index = switch_line;
                bigger = matrix[switch_line][pivot];
            }
        }
        /*e depois se for necessária a troca*/
        if(index != pivot){
            /*chama as funções de trocar linhas da matriz*/
            switch_lines(matrix[pivot],matrix[index],size);
            /*e de trocar posições do vetor de termos independentes*/
            switch_independent_terms(&vector[pivot],&vector[index]);
        }
        /*depois de verifica a necessidade de troca, começa a realmente fazer as operações na matriz*/
        /*laço de repetição agora para encontrar os multiplicadores*/
        for(int j = pivot + 1; j < size; j++){
            /*o multiplicador é a divisão do elemento a ser zerado pela linha pivo*/
            multiplier = matrix[j][pivot]/matrix[pivot][pivot];
            /*o outro laço mais interno serve para realizar as operações com o multiplicador encontrado*/
            for(int k = 0; k < size; k++){
                /*depois faz multiplicação do elemento da linha pivo com o multiplicador e soma
                com o a linha a ser zerada*/
                matrix[j][k] = matrix[j][k] - (multiplier * matrix[pivot][k]);
            }
            /*o vetor de termos independentes também será multiplicado e somado*/
            vector[j] = vector[j] - (multiplier * vector[pivot]);
        } 
    }
    /*começa agora a substituição retroativa*/
    x[size - 1] = vector[size - 1]/matrix[size - 1][size - 1];
    /*variavel soma, que será util para realizar a substituação*/
    double sum;
    /*for externo para caminhar nas linhas da matriz*/
    for(int i = (size - 1) - 1; i >= 0; i--){
        /*zera a soma*/
        sum = 0;
        /*for interno para caminhar nas colunas da matriz*/
        for(int j = i + 1; j < size; j++){
            /*realiza o soma do valor*/
            sum = sum + matrix[i][j] * x[j];
        }
        /*acrescenta no vetor*/
        x[i] = (vector[i] - sum)/matrix[i][i]; 
    }
    /*no final espera-se retornar um vetor com os valores que resolvem o sistema linear*/
    return(x);
}
