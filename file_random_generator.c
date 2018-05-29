#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
            /*primeiro valor, número de pontos tabelados para x e y*/
            int amount_tab_points = rand() % 10 + 1;
            /*vetor de pontos de x*/
            double xtab_points[amount_tab_points];
            /*vetor de pontos de y*/
            double ytab_points[amount_tab_points];
            /*intervalos de integração*/
            double a = 0;
            double b = 0;
            /*quantidade de pontos a serem interpolados*/
            int amount_interpolation_points = rand() % 10 + 1;
            /*vetor de pontos a serem interpolados*/
            double interpolation_points[amount_interpolation_points];
            /*variavel int com a quantidade de trapezios*/
            int trapezium = rand() % 100 + 1;
            /*zera contador para verificar quando os valores são diferentes de 0*/
            counter = 0;
            /*pontos de x*/
            while(counter != amount_tab_points){
                /*gera o número pseudo aleatório*/
                value = (double)(rand() % 10000) / (rand() % 1000 + 1) * (rand() % 2 - rand() % 2);
                if(value != 0){
                    /*verifica se é diferente de 0, se for*/
                    /*salva no vetor e incrementa o contador*/
                    xtab_points[counter] = value;
                    counter++;
                }
            }
            /*ordena o vetor*/
            selectionsort(xtab_points,amount_tab_points);
            /*pontos de y*/
            /*zera novamente o contador*/
            counter = 0;
            while(counter != amount_tab_points){
                /*gera o número pseudo aleatório*/
                value = (double)(rand() % 10000) / (rand() % 1000 + 1) * (rand() % 2 - rand() % 2);
                if(value != 0){
                    /*verifica se é diferente de 0, se for*/
                    /*salva no vetor e incrementa o contador*/
                    ytab_points[counter] = value;
                    counter++;
                }
            }
            /*ordena o vetor*/
            selectionsort(ytab_points,amount_tab_points);
            /*gera os valores dos intervalos de integração*/
            while(a == 0 || b == 0 || a == b) {
                /*enquanto foram iguais ou algum deles igual a 0, continuam gerando novos valores*/
                a = (double)(rand() % 10000 + 1) / (rand() % 1000 + 1) * (rand() % 2 - rand() % 2);
                b = (double)(rand() % 10000 + 1) / (rand() % 1000 + 1) * (rand() % 2 - rand() % 2);
            }
            /*verifica se o a é maior que o b*/
            if(a > b){
                /*se for troca eles*/
                double temp = a;
                a = b;
                b = temp;
            }
            /*zera novamente o contador*/
            counter = 0;
            while(counter != amount_interpolation_points){
                /*gera o número pseudo aleatório*/
                value = (double)(rand() % 10000) / (rand() % 1000 + 1) * (rand() % 2 - rand() % 2);
                if(value != 0){
                    /*verifica se é diferente de 0, se for*/
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