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
x.tab <- c(-4.500000,-1.800000,1.000000,1.500000);
y.tab <- c(1400.687500,4.504000,25.000000,67.187500);

#Pontos interpolados, calculados pelo 'trapezium'
x.int <- c(-1.000000,0.250000);
y.int <- c(-75.000000,-39.453125);

# Coeficientes do polinomio interpolador
coef <- c(-56.750000,62.000000,31.750000,-12.000000);

# Numero de pontos da tabela
n.tab <- 4;

# Numero de pontos a interpolar
n.int <- 2;

# Numero de trapezios
n.tpz <- 47

# Titulo
titulo <- 'P(x) = -56.750000*x^0 + 62.000000*x^1 + 31.750000*x^2 + -12.000000*x^3'

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