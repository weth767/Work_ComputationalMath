#ifndef TRAPEZIUM_RULE_H
#define TRAPEZIUM_RULE_H
/*função da regra do trapezio, que retornará a área total dos trápezios, implementando o requisito
7 - Cálculo da área do trapezio e requisito 8 - Cálculo da integral de pn(x)*/
/*recebe os intervalos a e b, a quantidade de trapezios, os coeficientes e o maior expoente*/
double trapezium_rule(double a, double b,int trapeziuns,double* coefficients,int bigger_expoent);
/*Espera-se como saída a área total dos trapézios envolvendo a função, que é o resultado da integral da 
função*/
#endif