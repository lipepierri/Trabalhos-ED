#include <stdio.h>

#define TAMANHO_STRING 64
#define TAMANHO_LISTA 1024



char listaDePalavras[TAMANHO_LISTA][TAMANHO_STRING];
int quantidade[TAMANHO_LISTA];



//funcoes equivalentes as da biblioteca string.h
void copiar(char * string1, char * string2) {
    int i = 0;
	
    for(i = 0; i < TAMANHO_STRING; i++) {
		string1[i] = string2[i];
	}
}

int comparar(char * string1, char * string2) {
    int i = 0;
	
    for(i = 0; i<  TAMANHO_STRING; i++) {
		//Testando tamanho das palavras
        if(string1[i] == '\0' && string2[i] == '\0') { return 0; }
        if(string1[i] == '\0' && string2[i] != '\0') { return -1; }
        if(string1[i] != '\0' && string2[i] == '\0') { return 1; }
		
        if(string1[i]>string2[i]) { return 1; }
        if(string1[i]<string2[i]) { return -1; }
    }
	
    return 0;
}



/*
 * QuickSort de palavras
 */
 void quickSort(int esquerda, int direita) {
 	char * pivot = listaDePalavras[direita];
 	int	i = esquerda, j = direita - 1, quant;
	
	char temp[TAMANHO_STRING];
 	
 	while(i < j) {
 		while(comparar(listaDePalavras[i], pivot) == -1 && i < j) { i++; }
 		while(comparar(listaDePalavras[j], pivot) == 1 && i < j) { j--; }
 		
 		if(i < j) {
			copiar(temp, listaDePalavras[i]);
 			copiar(listaDePalavras[i], listaDePalavras[j]);
 			copiar(listaDePalavras[j], temp);
			
			quant = quantidade[i];
			quantidade[i] = quantidade[j];
			quantidade[j] = quant;
 		}
 	}
 	
	i = esquerda;
	while(comparar(listaDePalavras[i], pivot) == -1){
		i++;
	}
	
	copiar(temp, listaDePalavras[i]);
	copiar(listaDePalavras[i], pivot);
	copiar(listaDePalavras[direita], temp);
	
	quant = quantidade[i];
	quantidade[i] = quantidade[direita];
	quantidade[direita] = quant;
 	
 	if(1 < i - esquerda) { quickSort(esquerda, i - 1); }
 	if(1 < direita - i) { quickSort(i + 1, direita); }
 }



//Main
int main(){
    char palavra[TAMANHO_STRING];
    int quant = 0;
	
    while(scanf("%s", palavra) != EOF) {
		int i;
        for(i = 0; i <= quant; i++){
            if(comparar(listaDePalavras[i], palavra) == 0) {
                //Palavra que ja apareceu
                quantidade[i]++;
				
                break;
            }
            if(i == quant) {
                //Palavra nova
                copiar(listaDePalavras[quant], palavra);
                quantidade[quant] = 1;
                quant++;
				
                break;
            }
        }
    }
	
    quickSort(0, quant - 1);
	
	int i;
    for(i = 0; i < quant; i++){
        printf("%s - %d\n", listaDePalavras[i], quantidade[i]);
    }
}
