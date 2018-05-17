#include <stdio.h>
#include <stdlib.h>
#include "file.h"

/*Função para ler o arquivo passado por parâmetro e devolve os dados para ser usados no arquivo
 principal do software 
*/
values read_file(char readfile[]){
    /*variaveis necessárias para a função*/
    char character;
    char helper[50];
    values v;
    /*abre o arquivo para a leitura*/
    FILE* file = fopen(readfile,"r");
    /*verifica se o ponteiro não está nulo, ou seja conseguiu abrir o arquivo*/
    if(file != NULL){
        /*laço de repetição que vai até o final do arquivo*/
        while(!(feof(file))){
            fscanf(file,"%c",&character);/*le o primeiro caractere da linha*/
            /*entra num seletor para verificar qual caractere foi lido*/
            switch(character){
                case 'n'://Número de pontos da tabela
                    getc(file);//pula o espaço após o  caractere lido
                    fscanf(file,"%i",&v.n);//lê o valor inteiro de n
                break;
                case 'x'://Lista com n valores de x da tabela
                    v.x = (float*)malloc(v.n * sizeof(float));//aloca espaço para o vetor de pontos de x
                    getc(file);//como o caractere x já foi lido, pula a o espaço
                    //e começa a leitura dos valores de x
                    for(int i = 0; i < v.n; i++){
                        fscanf(file,"%f",&v.x[i]);//pega o valor float
                        getc(file);//pula o espaço e vai para o próximo float
                    }
                    /*sai do laço nessa repetição para pegar o valor de y na proxima*/
                    continue;
                break;
                case 'y'://Lista com n valores de y da tabela
                    v.y = (float*)malloc(v.n * sizeof(float));//aloca espaço para o vetor de pontos de y
                    getc(file);//como o caractere y já foi lido, pula a o espaço
                    //e começa a leitura dos valores de y
                    for(int i = 0; i < v.n; i++){
                        fscanf(file,"%f",&v.y[i]);//pega o valor float
                        getc(file);//pula o espaço e vai para o próximo float
                    }
                break;
                case 'a'://Limite inferior do intervalo para o cálculo da integral definida
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%i",&v.a);//pega o valor inteiro de a
                break;
                case 'b'://Limite superior do intervalor para o cálculo da integral definida
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%i",&v.b);//pega o valor inteiro de b
                break;
                case 'i'://Número de pontos em min(x) e max(x) a ser interpolado
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%i",&v.i);//pega o valor inteiro de i
                break;
                case 'p'://Lista com i pontos a interpolar
                    v.p = (float*)malloc(v.i * sizeof(float));
                    getc(file);//como o caractere p já foi lido, pula a o espaço
                    //e começa a leitura dos valores de p
                    for(int i = 0; i < v.i; i++){
                        fscanf(file,"%f",&v.p[i]);//pega o valor float
                        getc(file);//pula o espaço e vai para o próximo float
                    }
                break;
                case 't'://Números de trapézios a implementar
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%i",&v.t);//pega o valor inteiro de t
                break;
                case '#':
                break;
                default://leitura do caractere de comentário, ou outro caractere que não deve ser lido
                    if(character != ' '  && character != '\n'){
                        printf("Formato do arquivo não corresponde ao formato permitido, abortando leitura!\n");
                        exit(1);
                    }
                break;
            }
            fscanf(file,"%[^\n]s",helper);//vai pro final da linha
            getc(file);//e pula para a próxima linha
        }
    }
    /*retorna a estrutura com os valores preenchidos pelos dados do arquivo*/
    return(v);
}