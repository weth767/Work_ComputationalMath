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
x.tab <- c(-1.250000,-0.888889,0.600000,1.200000);
y.tab <- c(0.500000,0.600000,1.125000,2.250000);

#Pontos interpolados, calculados pelo 'trapezium'
x.int <- c(-1.052632,0.866667);
y.int <- c(0.568329,1.516404);

# Coeficientes do polinomio interpolador
coef <- c(0.704432,0.316076,0.472989,0.280771);

# Numero de pontos da tabela
n.tab <- 4;

# Numero de pontos a interpolar
n.int <- 2;

# Numero de trapezios
n.tpz <- 83

# Titulo
titulo <- 'P(x) = 0.704432*x^0 + 0.316076*x^1 + 0.472989*x^2 + 0.280771*x^3'

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