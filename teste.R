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
x.tab <- c(-13.415929,-8.425159,5.464286,9.410638,14.638945,15.096257,20.928899,21.658635);
y.tab <- c(-17.376426,-10.326353,-0.583450,1.915935,7.205056,7.696275,14.806552,15.284722);

#Pontos interpolados, calculados pelo 'trapezium'
x.int <- c(-59.369231,-17.596364,-4.639900,2.533679,2.599419,8.836182,62.259259,97.787234);
y.int <- c(654087.316990,126.085453,1.412793,-0.100880,-0.134950,1.399725,-175290.070165,-6270375.905124);

# Coeficientes do polinomio interpolador
coef <- c(1.651338,-0.739325,-0.037084,0.025412,-0.001184,-0.000068,0.000006,-0.000000);

# Numero de pontos da tabela
n.tab <- 8;

# Numero de pontos a interpolar
n.int <- 8;

# Numero de trapezios
n.tpz <- 44

# Titulo
titulo <- 'P(x) = 1.651338*x^0 + -0.739325*x^1 + -0.037084*x^2 + 0.025412*x^3 + -0.001184*x^4 + -0.000068*x^5 + 0.000006*x^6 + -0.000000*x^7'

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