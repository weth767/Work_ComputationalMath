#include <stdio.h>
#include <stdlib.h>
#include "horner.h"
/*função da regra do trapezio, que retornará a área total dos trápezios*/
/*recebe os intervalos, a quantidade de trapezios, os coeficientes e o maior expoente*/
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
        area = area + ((polynomial_horner(coefficients,point_b,bigger_expoent) + polynomial_horner(coefficients,point_a,bigger_expoent)) / 2);
        /*atualiza os pontos*/
        point_a = point_a + height;
        point_b = point_b + height;
    }
    /*e no fim retorna a area total*/ 
    return area;
   
}