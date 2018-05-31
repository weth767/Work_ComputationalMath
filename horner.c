#include <stdio.h>
#include <stdlib.h>
#include "horner.h"
#include "gauss_pivoting.h"
/*função de horner, para resolução do polinomio, ou seja encontrar a imagem, para interpolar a função e 
utilizar os valores de y na função do trapezio, implementando o requisito 6 do trabalho*/
/*função para executar a função de horner nos valores de x que serão recebidos do arquivo
texto*/
/*recebe os coeficientes, o maior expoente, e o valor de x a ser substituido no polinomio*/
double polynomial_horner(double*coefficients, int bigger_expoent, double x){
	/*variavel y que receberá o valor final da imagem do polinomio segundo o x substituido*/
	double y = 0;
	/*recebe o ultimo coefiente*/
	y = coefficients[bigger_expoent - 1];
	/*laço de repetição que executa até o valor do menor expoente*/
	for(int i = bigger_expoent - 2 ; i >= 0; i--){
		/*o valor de y, será atualizado com os valores dos coeficientes multiplicado por x*/
		y = y * x + coefficients[i];
	}
	/*como saída, espera-se o valor da imagem correto referente a função e o 'x' recebido*/
	return y;
}

