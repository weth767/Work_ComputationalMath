#ifndef INTERPOLATION_H
#define INTERPOLATION_H
/*função para realizar a interpolação dos pontos recebidos do arquivo a partir dos coeficientes 
encontrados pela eliminação de gauss, tratando de parte do requisito 4 - Determinação Polinônio interpolador*/
/*recebe os coeficientes, os pontos a serem interpolados(x) na função, quantidade de pontos e o maior
expoente*/
double * interpolation(double * coefficients, double * points, int amount, int bigger_expoent);
 /*no fim, espera-se retornar um vetor, com as imagens referentes aos pontos que foram interpolados*/
#endif