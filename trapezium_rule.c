#include <stdio.h>
#include <stdlib.h>
#include "horner.h"
/**/
/*função da regra do trapezio, que retornará a área total dos trápezios, implementando o requisito
7 - Cálculo da área do trapezio e requisito 8 - Cálculo da integral de pn(x)*/
/*recebe os intervalos a e b, a quantidade de trapezios, os coeficientes e o maior expoente*/
double trapezium_rule(double a, double b,int trapeziuns,double* coefficients,int bigger_expoent){
    /*pega a altura que é a razão entre a diferença do intervalo dividido pela quantidade de trapezios*/
    double height = (b - a)/trapeziuns;
    /*o ponto a inicia com o próprio a, que seria o inicio do trapezio*/
    double point_a = a;
    /*o ponto b inicia com o a + a altura, que seria o fim do trapezio*/
    double point_b = a + height;
    /*inicia a área com 0*/
    double area = 0;
    /*e até que o ponto b seja diferente do intervalo final de integração*/
    /*executa um laço que vai somando as áreas, executa o número de trapezios vezes*/
    for(int i = 0; i < trapeziuns; i++){
        /*a área recebe ela mesma, mais a regra do trapezio dos pontos a e b*/
        area = area + (((polynomial_horner(coefficients,bigger_expoent,point_b) + polynomial_horner(coefficients,bigger_expoent,point_a))* height) / 2);
        /*atualiza os pontos*/
        point_a = point_a + height;
        point_b = point_b + height;
    }
    /*Espera-se como saída a área total dos trapézios envolvendo a função, que é o resultado da integral da 
    função*/ 
    return area;
}