#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define TAM 4
#define POPULACAO 100
#define GERACOES 50
#define MUTACAO 0.1

//estrutura que representa o cromossomo
struct individuo{
	int genes[TAM];
	double avaliacao;
	double avaliacaoParcial;
};

typedef struct individuo Individuo;

double avaliar(Individuo *populacao);

int binarioInteiro(int *numero);

void criarPopulacao(Individuo *populacao);

void crossover(int pai1, int pai2, Individuo *populacao, Individuo* novaPopulacao, int contIndividuos);

double funcaoAvaliacao(int x);

double melhorIndividuo(Individuo *populacao);

void modulo(Individuo *populacao, Individuo* novaPopulacao);

void mutacao(Individuo* novaPopulacao, int tamanho);

int selecao(Individuo *populacao, double somaTotal);

void visualizarPopulacao(Individuo *populacao);

//reponsavel pelo controle das gerações
int main(){
	
	Individuo populacao[POPULACAO];
	Individuo novaPopulacao[POPULACAO];
	
	int pai1, pai2;//armazenar os indices dos pais selecionados
	int contIndividuos = 0, contador = 0, somaTotal;
	
	srand(time(NULL));
	
	criarPopulacao(populacao);
	
	for(contador=0; contador<GERACOES; ++contador){
		somaTotal = avaliar(populacao);
		
		for(contIndividuos=0; contIndividuos < POPULACAO; ++contIndividuos){
			
			pai1 = selecao(populacao, somaTotal);
			pai2 = selecao(populacao, somaTotal);
			
			crossover(pai1, pai2, populacao, novaPopulacao, contIndividuos);
			
			mutacao(populacao, contIndividuos);
		}
		modulo(populacao, novaPopulacao);
	}
	
	somaTotal = avaliar(populacao);
	
	
	printf("A melhor solucao da ultima geracao foi: %lf \n", melhorIndividuo(populacao));
	
	visualizarPopulacao(populacao);
	return 0;
}

double funcaoAvaliacao(int x){
	return x*1.0;
}

//identifica qual o melhor individuo do vetor da população
double melhorIndividuo(Individuo *populacao){
	int cont, j;
	double melhor; 
	
	//recebendo o primeiro elemento
	melhor = populacao[0].avaliacao;
	
	for(cont=1; cont<POPULACAO; ++cont){
		
		if(melhor<populacao[cont].avaliacao){
			melhor = populacao[cont].avaliacao;
		}
	}
	return melhor;
}

int selecao(Individuo *populacao, double somaTotal){
	double valor;
	int cont = 0;
	valor = rand() % (int)somaTotal;
	
	for(cont = 0; cont<POPULACAO ;++cont){
		if(valor <= populacao[cont].avaliacaoParcial){
			return cont;
		}
	}
}

void crossover(int pai1, int pai2, Individuo *populacao, Individuo* novaPopulacao, int contIndividuos){
	int cont;
	
	for(cont = 0; cont<TAM; ++cont){
		if((rand() % 2) == 0){
			novaPopulacao[contIndividuos].genes[cont] = populacao[pai1].genes[cont];
		}else{
			novaPopulacao[contIndividuos].genes[cont] = populacao[pai2].genes[cont];
		}
	}	
}

void mutacao(Individuo* novaPopulacao, int tamanho){
	int cont;
	
	for(cont = 0; cont<TAM; ++cont){
		if(rand() < MUTACAO){
			novaPopulacao[tamanho].genes[cont] = (novaPopulacao[tamanho].genes[cont]+1)/2;
		}
	}
}


double avaliar(Individuo *populacao){
	int i, j, x;
	double total = 0;
	
	for(i=0; i<POPULACAO; ++i){
		for(j=0; j<TAM; ++j){
			x = binarioInteiro(populacao[i].genes);
			populacao[i].avaliacao = funcaoAvaliacao(x);
			total += populacao[i].avaliacao;
			populacao[i].avaliacaoParcial = total;
		}
	}
	
	return total;
}

int binarioInteiro(int *numero){
	int i;
	int valor = 0;
	int base = 1;
	
	for(i=(TAM-1); i>=0; --i){
		valor += numero[i]*base;
		base*=2;
	}
	return valor;
}

void criarPopulacao(Individuo *populacao){
	int i, j;
	
	for(i=0; i<POPULACAO; ++i){
		for(j=0; j<TAM; ++j){
			populacao[i].genes[j] = rand() % 2;
		}
	}
}

void visualizarPopulacao(Individuo *populacao){
	int i, j;
	
	for(i=0; i<POPULACAO; ++i){
		printf("%d -\t", i);
		for(j=0; j<TAM; ++j){
			printf("%d ",populacao[i].genes[j]);
		}
		printf(" - %lf \t\n",populacao[i].avaliacao);
	}
	
}

void modulo(Individuo *populacao, Individuo* novaPopulacao){
	int cont, contGene;
	
	for(cont=0; cont<TAM; ++cont){
		for(contGene=0; contGene < TAM; ++contGene){
			populacao[cont].genes[contGene] = novaPopulacao[cont].genes[contGene];
		}
	}
}
