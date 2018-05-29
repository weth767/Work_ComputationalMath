#ifndef INTERPOLATION_H
#define INTERPOLATION_H
/*função para realizar a interpolação da função, segundo os coefientes encontrados após a eliminação 
de gauss e a partir de x, encontrar a imagem.*/
double * interpolation(double * coefficients, double * points, int amount, int bigger_expoent);

#endif