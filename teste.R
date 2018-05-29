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
x.tab <- c(-9.930801,-8.087719,-5.645530,-2.977483,-0.246702,3.421118,8.797990,15.058632);
y.tab <- c(-16.614173,-1.895916,6.279476,8.664678,9.553514,12.306483,30.873239,453.272727);

#Pontos interpolados, calculados pelo 'trapezium'
x.int <- c(-35.437500,-8.460581,-4.637405,2.686352,4.554054,5.547009,7.018967,8.259184,25.992063,997.500000);
y.int <- c(-677505122295.136108,-29824885.835789,-441276.354271,9951.273817,397141.712029,1576424.663752,8171845.856405,25496994.329233,77623588843.132904,9499212973398474883072.000000);

# Coeficientes do polinomio interpolador
coef <- c(9.666644,0.478989,0.084212,0.005312,-0.002104,0.000117,0.000019,0.000001);

# Numero de pontos da tabela
n.tab <- 8;

# Numero de pontos a interpolar
n.int <- 10;

# Numero de trapezios
n.tpz <- 94

# Titulo
titulo <- 'P(x) = 9.666644*x^0 + 0.478989*x^1 + 0.084212*x^2 + 0.005312*x^3 + -0.002104*x^4 + 0.000117*x^5 + 0.000019*x^6 + 0.000001*x^7'

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