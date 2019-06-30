#include <cstdio>
#define TAMANHO 256
#define CAGUEI break

//Pilhas
int numerosPilha[2*TAMANHO];
int numerosTopo = -1;

char operadoresPilha[TAMANHO];
int operadoresTopo = -1;

//String
char string[4*TAMANHO];



//Prototipos
void reconhecedorDeCharmander(int * posicao);
void desempilharAsPilhas();
int reconhecedorDeNumero(int * posicao);

void numerosPush(int numero);
int numerosPop();

void operadoresPush(char operador);
int operadoresPop();



//Famoso main
int main() {
	int posicaoStr = 0;
	
	scanf("%s", string);
	
	while(string[posicaoStr] != '\0') {
		reconhecedorDeCharmander(&posicaoStr);
	}
	
	printf("%d\n", numerosPilha[numerosTopo]);
	
	
	
	return 0;
}



//Funcoes mais complexas
void reconhecedorDeCharmander(int * posicao) {
	switch(string[posicao[0]]) {
		//Parenteses
		case '(':
			CAGUEI;
		case ')':
			desempilharAsPilhas();
			CAGUEI;
		
		//Operadores
		case '+':
			operadoresPush('+');
			CAGUEI;
		case '-':
			operadoresPush('-');
			CAGUEI;
		case '*':
			operadoresPush('*');
			CAGUEI;
		case '/':
			operadoresPush('/');
			CAGUEI;
		
		//Numeros
		default:
			int numWhile = string[posicao[0]] - 48;
			if((0 <= numWhile) && (numWhile <= 9)) {
				numerosPush(reconhecedorDeNumero(posicao));
			}
	}
	
	posicao[0]++;
}

void desempilharAsPilhas() {
	int numEsquerda, numDireita;
	char operador;
	
	numDireita = numerosPop();
	numEsquerda = numerosPop();
	
	operador = operadoresPop();
	
	
	
	switch(operador) {
		case '+':
			numerosPush(numEsquerda + numDireita);
			CAGUEI;
		case '-':
			numerosPush(numEsquerda - numDireita);
			CAGUEI;
		case '*':
			numerosPush(numEsquerda * numDireita);
			CAGUEI;
		case '/':
			numerosPush(numEsquerda / numDireita);
			CAGUEI;
	}
}

int reconhecedorDeNumero(int * posicao) {
	int numeroTemp = 0;
	int numeroWhile = string[posicao[0]] - 48;
	
	while((0 <= numeroWhile) && (numeroWhile <= 9)) {
		numeroTemp = numeroTemp*10 + numeroWhile; //numero xy -> x = 10*x + y
		
		posicao[0]++;
		numeroWhile = string[posicao[0]] - 48;
	}
	
	posicao[0]--;
	
	
	
	return numeroTemp;
}



//Funcoes de pilha
void numerosPush(int numero) {
	numerosTopo++;
	numerosPilha[numerosTopo] = numero;
}

int numerosPop() {
	int numeroTemp = numerosPilha[numerosTopo];
	numerosTopo--;
	
	return numeroTemp;
}



void operadoresPush(char operador) {
	operadoresTopo++;
	operadoresPilha[operadoresTopo] = operador;
}

int operadoresPop() {
	int operadorTemp = operadoresPilha[operadoresTopo];
	operadoresTopo--;
	
	return operadorTemp;
}
