#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double polynomial_horner(int*coefficients, int bigger_expoent, double x){
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

/*função para a troca dos valores*/
void swap(double *x, double *y){
	double temp = *x;
	*x = *y;
	*y = temp;
}

//função de seleção
void selectionsort(double vector[], int size){
	//variavel temporaria para guardar valor na troca
	int temp;
	int lower_index;
	//dois laços de repetição que irão verificar todo o vetor
	for(int i = 0; i < size; i++){
		lower_index = i;
		//consira o i atual com menor indice;
		for(int j = i + 1; j < size; j++){
			if(vector[j] < vector[lower_index]){
				//pega o menor indice, caso o valor da posição de j for menor que a do menor indice
				lower_index = j;
			}
		}
		//chama a função de troca
		swap(&vector[lower_index],&vector[i]);
	}
}
/*função principal*/
int main(int argc, char *argv[]){
    /*variavel string para pegar o caminho do arquivo*/
    char path_file[100];
    /*verifica se foi passado o formato correto para inicio do software */
    if(argv[1] != NULL && argc == 2){
        /*string recebe o caminho do arquivo*/
        strcpy(path_file,argv[1]);
        /*abre o arquivo*/
        FILE *file = fopen(path_file,"w");
        /*verifica se o ponteiro recebeu algo*/
        if(file != NULL){
            /*variavel contador*/
            int counter;
            double value;
            /*seta a semente para os números pseudo aleatórios*/
            srand(time(NULL));
            /*tamanho da função original*/
            int size_function = rand() % 6 + 1;
            /*vetor dos coeficientes*/
            int coefficients[size_function];
            /*preenche esse vetor com coeficientes aleatorios*/
            for(int i = 0; i < size_function; i++){
                coefficients[i] = rand() % 10 + 1;
            }
            /*primeiro valor, número de pontos tabelados para x e y*/
            int amount_tab_points = rand() % 6 + 2;
            /*vetor de pontos de x*/
            double xtab_points[amount_tab_points];
            /*vetor de pontos de y*/
            double ytab_points[amount_tab_points];
            /*intervalos de integração*/
            double a = 0;
            double b = 0;
            /*quantidade de pontos a serem interpolados*/
            int amount_interpolation_points = rand() % 6 + 1;
            /*vetor de pontos a serem interpolados*/
            double interpolation_points[amount_interpolation_points];
            /*variavel int com a quantidade de trapezios*/
            int trapezium = rand() % 100 + 1;
            /*zera contador para verificar quando os valores são diferentes de 0*/
            counter = 0;
            /*pontos de x*/
            while(counter != amount_tab_points){
                /*gera o número pseudo aleatório*/
                value = (double)(rand() % 10) / (rand() % 5 + 1) * (rand() % 2 - rand() % 2);
                if(value != 0){
                    /*verifica se é diferente de 0, se for*/
                    /*salva no vetor e incrementa o contador*/
                    xtab_points[counter] = value;
                    counter++;
                }
            }
            /*ordena o vetor*/
            selectionsort(xtab_points,amount_tab_points);
            /*preencher os valores de y*/
            for(int j = 0; j < amount_tab_points; j++){
                /*for para aplicar o horner na e resolver os valores de x segundo os coeficientes*/
                ytab_points[j] = polynomial_horner((int*)coefficients,size_function,xtab_points[j]); 
            }
            /*gera os valores dos intervalos de integração*/
            while(a == 0 || b == 0 || a == b) {
                /*enquanto foram iguais ou algum deles igual a 0, continuam gerando novos valores*/
                a = (double)(rand() % 10 + 1) / (rand() % 5 + 1) * (rand() % 2 - rand() % 2);
                b = (double)(rand() % 10 + 1) / (rand() % 5 + 1) * (rand() % 2 - rand() % 2);
            }
            /*verifica se o a é maior que o b*/
            if(a > b){
                /*se for troca eles*/
                double temp = a;
                a = b;
                b = temp;
            }
            /*zera novamente o contador*/
            /*preenche os pontos de interpolação*/
            counter = 0;
            while(counter != amount_interpolation_points){
                /*gera o número pseudo aleatório*/
                value = (double)(rand() % 10) / (rand() % 5 + 1) * (rand() % 2 - rand() % 2);
                if(value != 0 && (value >= a && value <= b)){
                    /*verifica se é diferente de 0 e se o valor está entre o intervalo a - b, se for*/
                    /*salva no vetor e incrementa o contador*/
                    interpolation_points[counter] = value;
                    counter++;
                }
            }
            /*ordena o vetor*/
            selectionsort(interpolation_points,amount_interpolation_points);
            /*e salva no arquivo*/
            fprintf(file,"#Lista de pontos tabelados [%lf,%lf]\n",xtab_points[0],xtab_points[amount_tab_points - 1]);
            fprintf(file,"n %i\n",amount_tab_points);
            fprintf(file,"# Função original: ");
            for(int i = size_function - 1; i >= 0; i--){
                if(i == 0){
                    fprintf(file,"%i\n",coefficients[i]);
                }
                else{
                    fprintf(file,"%i*x^%i + ",coefficients[i],i);
                }
            }
            fprintf(file,"x ");
            for(int i = 0; i < amount_tab_points; i++){
                if(i == amount_tab_points - 1){
                    fprintf(file,"%lf\n",xtab_points[i]);
                }
                else{
                    fprintf(file,"%lf ",xtab_points[i]);
                }
            }
            fprintf(file,"y ");
            for(int i = 0; i < amount_tab_points; i++){
                if(i == amount_tab_points - 1){
                    fprintf(file,"%lf\n",ytab_points[i]);
                }
                else{
                    fprintf(file,"%lf ",ytab_points[i]);
                }
            }
            fprintf(file,"# Intervalo da integral definida em [%lf,%lf]\n",a,b);
            fprintf(file,"a %lf\n",a);
            fprintf(file,"b %lf\n",b);
            fprintf(file,"# Lista de pontos a interpolar\n");
            fprintf(file,"i %i\n",amount_interpolation_points);
            fprintf(file,"p ");
            for(int i = 0; i < amount_interpolation_points; i++){
                if(i == amount_interpolation_points - 1){
                    fprintf(file,"%lf\n",interpolation_points[i]);
                }
                else{
                    fprintf(file,"%lf ",interpolation_points[i]);
                }
            }
            fprintf(file,"# Computar integral com %i trapezios\n",trapezium);
            fprintf(file,"t %i",trapezium);
        }
        fclose(file);
    }
    return(0);
}