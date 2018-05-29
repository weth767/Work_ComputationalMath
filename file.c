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
                    v.x = (double*)malloc(v.n * sizeof(double));//aloca espaço para o vetor de pontos de x
                    getc(file);//como o caractere x já foi lido, pula a o espaço
                    //e começa a leitura dos valores de x
                    for(int i = 0; i < v.n; i++){
                        fscanf(file,"%lf",&v.x[i]);//pega o valor double
                        getc(file);//pula o espaço e vai para o próximo double
                    }
                    /*sai do laço nessa repetição para pegar o valor de y na proxima*/
                    continue;
                break;
                case 'y'://Lista com n valores de y da tabela
                    v.y = (double*)malloc(v.n * sizeof(double));//aloca espaço para o vetor de pontos de y
                    getc(file);//como o caractere y já foi lido, pula a o espaço
                    //e começa a leitura dos valores de y
                    for(int i = 0; i < v.n; i++){
                        fscanf(file,"%lf",&v.y[i]);//pega o valor double
                        getc(file);//pula o espaço e vai para o próximo double
                    }
                break;
                case 'a'://Limite inferior do intervalo para o cálculo da integral definida
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%lf",&v.a);//pega o valor inteiro de a
                break;
                case 'b'://Limite superior do intervalor para o cálculo da integral definida
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%lf",&v.b);//pega o valor inteiro de b
                break;
                case 'i'://Número de pontos em min(x) e max(x) a ser interpolado
                    getc(file);//pula o espaço após o caractere lido
                    fscanf(file,"%i",&v.i);//pega o valor inteiro de i
                break;
                case 'p'://Lista com i pontos a interpolar
                    v.p = (double*)malloc(v.i * sizeof(double));
                    getc(file);//como o caractere p já foi lido, pula a o espaço
                    //e começa a leitura dos valores de p
                    for(int i = 0; i < v.i; i++){
                        fscanf(file,"%lf",&v.p[i]);//pega o valor double
                        getc(file);//pula o espaço e vai para o próximo double
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

void data_out(char path_out[100],values v,double *x,double *y,double area){
    FILE *file = fopen(path_out,"w");
    if(file != NULL){
        fprintf(file,"######################################################################\n");
        fprintf(file,"#Script automatico gerado por ‘trapezium’, software de interpolação #\n");
        fprintf(file,"#e integracao numérica                                              #\n");
        fprintf(file,"######################################################################\n\n");
        fprintf(file,"#\n#Parametros. Devem ser preenchidos pelo software\n#\n\n");
        fprintf(file,"#Nome da figura\nnome <- 'saida.png'\n\n");
        fprintf(file,"#Dados tabelados\n");
        fprintf(file,"x.tab <- c(");
        for(int i = 0; i < v.n; i++){
            if(i == v.n - 1){
                fprintf(file,"%lf",v.x[i]);    
            }
            else{
                fprintf(file,"%lf,",v.x[i]);
            }
        }
        fprintf(file,");\n");
        fprintf(file,"y.tab <- c(");
        for(int i = 0; i < v.n; i++){
            if(i == v.n - 1){
                fprintf(file,"%lf",v.y[i]);    
            }
            else{
                fprintf(file,"%lf,",v.y[i]);
            }
        }
        fprintf(file,");\n\n");
        fprintf(file,"#Pontos interpolados, calculados pelo 'trapezium'\n");
        fprintf(file,"x.int <- c(");
        for(int i = 0; i < v.i; i++){
            if(i == v.i - 1){
                fprintf(file,"%lf",v.p[i]);    
            }
            else{
                fprintf(file,"%lf,",v.p[i]);
            }
        }
        fprintf(file,");\n");
        fprintf(file,"y.int <- c(");
        for(int i = 0; i < v.i; i++){
            if(i == v.i - 1){
                fprintf(file,"%lf",y[i]);    
            }
            else{
                fprintf(file,"%lf,",y[i]);
            }
        }
        fprintf(file,");\n\n");
        fprintf(file,"# Coeficientes do polinomio interpolador\n");
        fprintf(file,"coef <- c(");
        for(int i = 0; i < v.n; i++){
            if(i == v.n - 1){
                fprintf(file,"%lf",x[i]);    
            }
            else{
                fprintf(file,"%lf,",x[i]);
            }
        }
        fprintf(file,");\n\n");
        fprintf(file,"# Numero de pontos da tabela\n");
        fprintf(file,"n.tab <- %i;\n\n",v.n);
        fprintf(file,"# Numero de pontos a interpolar\n");
        fprintf(file,"n.int <- %i;\n\n",v.i);
        fprintf(file,"# Numero de trapezios\n");
        fprintf(file,"n.tpz <- %i\n\n",v.t);
        fprintf(file,"# Titulo\n");
        fprintf(file,"titulo <- 'P(x) = ");
        for(int i = 0; i < v.n; i++){
            if(i == v.n - 1){
                fprintf(file,"%lf*x^%i'\n\n",x[i],i);
            }
            else{
                fprintf(file,"%lf*x^%i + ",x[i],i);
            }
        }
        fprintf(file,"#\n# Esta parte do script deve funcionar desde que os parametros\n");
        fprintf(file,"# acima estejam devidamente preenchidos. E' a parte estatica\n");
        fprintf(file,"# do script. Copiar exatamente desta forma no arquivo de saida.\n#\n\n");
        fprintf(file,"#calcula o valor interpolado para o ponto x\n");
        fprintf(file,"polinomio <- function(x, coef, n){\n");
        fprintf(file,"\tresultado <- 0;\n");
        fprintf(file,"\tfor(i in 1:n){\n");
        fprintf(file,"\t\tresultado <- resultado + coef[i] * (x^(i - 1));\n");
        fprintf(file,"\t}\n");
        fprintf(file,"\treturn(resultado);\n");
        fprintf(file,"}\n\n");
        fprintf(file,"#\n#Aqui começam os comandos para plotar os resultados\n#\n\n");
        fprintf(file,"# Cria o arquivo .png\n");
        fprintf(file,"png(nome);\n\n");
        fprintf(file,"# Gerando figura com 100 pontos\n");
        fprintf(file,"gap <- (max(x.tab) - min(x.tab)) / 100;\n");
        fprintf(file,"x <- seq(min(x.tab),max(x.tab),gap);\n");
        fprintf(file,"y <- polinomio(x, coef, n.tab);\n");
        fprintf(file,"plot(x,y,type='l', main = titulo);\n\n");
        fprintf(file,"#Plota os trapezios\n");
        fprintf(file,"h <- (max(x.tab) - min(x.tab)) / n.tpz;\n");
        fprintf(file,"xp <- seq(min(x.tab), max(x.tab), h);\n");
        fprintf(file,"yp <- polinomio(xp, coef, n.tab);\n");
        fprintf(file,"for(i in 1:(n.tpz)){\n");
        fprintf(file,"\tpolygon(c(xp[i], xp[i], xp[i+1], xp[i+1], xp[i]),c(0, yp[i], yp[i+1], 0, 0),col='yellow', border='black', lty=2, lwd=1.3);\n");
        fprintf(file,"}\n\n");
        fprintf(file,"#Pontos da tabela\n");
        fprintf(file,"for(i in 1:n.tab){\n");
        fprintf(file,"\tpoints(x.tab[i],y.tab[i],col='red',pch=19);\n");
        fprintf(file,"}\n\n# Pontos interpolados\n");
        fprintf(file,"for(i in 1:n.tab){\n");
        fprintf(file,"\tpoints(x.int[i],y.int[i],col='blue',pch=19);\n");
        fprintf(file,"}\n\n");
        fprintf(file,"# Encerra a criação do arquivo .png\n");
        fprintf(file,"dev.off();");
    }
    fclose(file);
}