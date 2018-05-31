######################################################################
#Script automatico gerado por ‘trapezium’, software de interpolação #
#e integracao numérica                                              #
######################################################################

#
#Parametros. Devem ser preenchidos pelo software
#

#Nome da figura
nome <- 'saida.png'

#Dados tabelados
x.tab <- c(-1.750000,-1.333333,-0.833333,0.500000,1.000000);
y.tab <- c(-5.000000,-0.400000,-0.250000,-0.166667,1.125000);

#Pontos interpolados, calculados pelo 'trapezium'
x.int <- c(-0.875000,0.400000);
y.int <- c(-0.162440,-0.504903);

# Coeficientes do polinomio interpolador
coef <- c(-1.412242,0.992809,3.629859,-0.447287,-1.638140);

# Numero de pontos da tabela
n.tab <- 5;

# Numero de pontos a interpolar
n.int <- 2;

# Numero de trapezios
n.tpz <- 9

# Titulo
titulo <- 'P(x) = -1.412242*x^0 + 0.992809*x^1 + 3.629859*x^2 + -0.447287*x^3 + -1.638140*x^4'

#
# Esta parte do script deve funcionar desde que os parametros
# acima estejam devidamente preenchidos. E' a parte estatica
# do script. Copiar exatamente desta forma no arquivo de saida.
#

#calcula o valor interpolado para o ponto x
polinomio <- function(x, coef, n){
	resultado <- 0;
	for(i in 1:n){
		resultado <- resultado + coef[i] * (x^(i - 1));
	}
	return(resultado);
}

#
#Aqui começam os comandos para plotar os resultados
#

# Cria o arquivo .png
png(nome);

# Gerando figura com 100 pontos
gap <- (max(x.tab) - min(x.tab)) / 100;
x <- seq(min(x.tab),max(x.tab),gap);
y <- polinomio(x, coef, n.tab);
plot(x,y,type='l', main = titulo);

#Plota os trapezios
h <- (max(x.tab) - min(x.tab)) / n.tpz;
xp <- seq(min(x.tab), max(x.tab), h);
yp <- polinomio(xp, coef, n.tab);
for(i in 1:(n.tpz)){
	polygon(c(xp[i], xp[i], xp[i+1], xp[i+1], xp[i]),c(0, yp[i], yp[i+1], 0, 0),col='yellow', border='black', lty=2, lwd=1.3);
}

#Pontos da tabela
for(i in 1:n.tab){
	points(x.tab[i],y.tab[i],col='red',pch=19);
}

# Pontos interpolados
for(i in 1:n.tab){
	points(x.int[i],y.int[i],col='blue',pch=19);
}

# Encerra a criação do arquivo .png
dev.off();