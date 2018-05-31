#include <stdio.h>
#include <stdlib.h>
#include "horner.h"
#include "interpolation.h"
/*função para realizar a interpolação dos pontos recebidos do arquivo a partir dos coeficientes 
encontrados pela eliminação de gauss, tratando de parte do requisito 4 - Determinação do Polinônio 
interpolador*/
/*recebe os coeficientes, os pontos a serem interpolados(x) na função, quantidade de pontos e o maior
expoente*/
double * interpolation(double * coefficients, double * points, int amount, int bigger_expoent){
    /*aloca espaço de memória para um vetor de imagens da função*/
    double * images = (double*)malloc(amount*sizeof(double));
    /*um laço de repetição que executa até a quantidade de pontos*/
    for(int i = 0 ; i < amount; i++){
        /*preenche o vetor de imagens com as imagens da função*/
        images[i] = polynomial_horner(coefficients,bigger_expoent,points[i]);
    }
    /*no fim, espera-se retornar um vetor, com as imagens referentes aos pontos que foram interpolados*/
    return(images);
}