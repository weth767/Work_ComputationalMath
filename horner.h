#ifndef HORNER_H
#define HORNER_H
/*função de horner, para resolução do polinomio, ou seja encontrar a imagem, para interpolar a função e 
utilizar os valores de y na função do trapezio, implementando o requisito 6 do trabalho*/
/*função para executar a função de horner nos valores de x que serão recebidos do arquivo
texto*/
/*recebe os coeficientes, o maior expoente, e o valor de x a ser substituido no polinomio*/
double polynomial_horner(double*coefficients, int bigger_expoent, double x);
/*como saída, espera-se o valor da imagem correto referente a função e o 'x' recebido*/
#endif