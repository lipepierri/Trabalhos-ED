#include <stdio.h>
#include <stdlib.h>



typedef struct str_AVLno {
	struct str_AVLno * esquerda, * direita;
	int altura, chave;
} AVLno;



AVLno * criarNo(int chave) {
	AVLno * novoNo = malloc(sizeof(AVLno));
	
	novoNo->chave = chave;
	novoNo->altura = 1;
	
	novoNo->esquerda = NULL;
	novoNo->direita = NULL;
	
	return novoNo;
}

int alturaNo(AVLno * no) {
	int alturaEsq, alturaDir;
	
	if(no->esquerda == NULL) {
		alturaEsq = 0;
	} else {
		alturaEsq = no->esquerda->altura;
	}
	if(no->direita == NULL) {
		alturaDir = 0;
	} else {
		alturaDir = no->direita->altura;
	}
	
	return 1 + ((alturaEsq < alturaDir) ? alturaDir : alturaEsq);
}

AVLno * esquerdaEsquerda(AVLno * noRaiz) {
	AVLno * noEsquerda = noRaiz->esquerda, * noMeio = noEsquerda->direita;
	
	noEsquerda->direita = noRaiz;
	noRaiz->esquerda = noMeio;
	
	noRaiz->altura = alturaNo(noRaiz);
	noEsquerda->altura = alturaNo(noEsquerda);
	
	return noEsquerda;
}

AVLno * esquerdaDireita(AVLno * noRaiz) {
	AVLno * noZ = noRaiz, * noY = noZ->esquerda, * noX = noY->direita,
		* noEsquerda = noX->esquerda, * noDireita = noX->direita;
	
	noX->direita = noZ;
	noZ->esquerda = noDireita;
	
	noX->esquerda = noY;
	noY->direita = noEsquerda;
	
	noX->altura = alturaNo(noX);
	noY->altura = alturaNo(noY);
	noZ->altura = alturaNo(noZ);
	
	return noX;
}

AVLno * direitaEsquerda(AVLno * noRaiz) {
	AVLno * noZ = noRaiz, * noY = noZ->direita, * noX = noY->esquerda,
		* noEsquerda = noX->esquerda, * noDireita = noX->direita;
	
	noX->direita = noY;
	noY->esquerda = noDireita;
	
	noX->esquerda = noZ;
	noZ->direita = noEsquerda;
	
	noX->altura = alturaNo(noX);
	noY->altura = alturaNo(noY);
	noZ->altura = alturaNo(noZ);
	
	return noX;
}

AVLno * direitaDireita(AVLno * noRaiz) {
	AVLno * noDireita = noRaiz->direita, * noMeio = noDireita->esquerda;
	
	noDireita->esquerda = noRaiz;
	noRaiz->direita = noMeio;
	
	noRaiz->altura = alturaNo(noRaiz);
	noDireita->altura = alturaNo(noDireita);
	
	return noDireita;
}

void inserirNormal(AVLno * raiz, int chave) {
	if(raiz == NULL) {
		return;
	}
	
	AVLno * it = raiz, * preIt = NULL, * novoNo = criarNo(chave);
	
	while(it != NULL) {
		preIt = it;
		
		if(chave < it->chave) {
			it = it->esquerda;
		} else {
			it = it->direita;
		}
	}
	
	if(chave < preIt->chave) {
		preIt->esquerda = novoNo;
	} else {
		preIt->direita = novoNo;
	}
}

AVLno * inserirNaAVL(AVLno * raiz, int chave) {
	if(raiz == NULL) {
		return criarNo(chave);
	}
	
	if(chave < raiz->chave) {
		raiz->esquerda = inserirNaAVL(raiz->esquerda, chave);
	} else {
		raiz->direita = inserirNaAVL(raiz->direita, chave);
	}
	
	
	
	int alturaEsq, alturaDir,
		balanca;
	
	AVLno * noX, * noY, * noZ = raiz;
	
	if(noZ->esquerda == NULL) {
		alturaEsq = 0;
	} else {
		alturaEsq = noZ->esquerda->altura;
	}
	if(noZ->direita == NULL) {
		alturaDir = 0;
	} else {
		alturaDir = noZ->direita->altura;
	}
	
	balanca = alturaDir - alturaEsq;
	
	
	
	if(balanca < -1) {
		noY = noZ->esquerda;
		
		if(noY->esquerda == NULL) {
			alturaEsq = 0;
		} else {
			alturaEsq = noY->esquerda->altura;
		}
		if(noY->direita == NULL) {
			alturaDir = 0;
		} else {
			alturaDir = noY->direita->altura;
		}
		
		if(alturaEsq < alturaDir) {
			return esquerdaDireita(noZ);
		} else {
			return esquerdaEsquerda(noZ);
		}
	}
	
	if(1 < balanca) {
		noY = noZ->direita;
		
		if(noY->esquerda == NULL) {
			alturaEsq = 0;
		} else {
			alturaEsq = noY->esquerda->altura;
		}
		if(noY->direita == NULL) {
			alturaDir = 0;
		} else {
			alturaDir = noY->direita->altura;
		}
		
		if(alturaEsq < alturaDir) {
			return direitaDireita(noZ);
		} else {
			return direitaEsquerda(noZ);
		}
	}
	
	raiz->altura = alturaNo(raiz);
	
	return raiz;
}

void imprimirPreOrdem(AVLno * raiz) {
	if(raiz == NULL) {
		return;
	}
	
	printf("%d\n", raiz->chave);
	
	imprimirPreOrdem(raiz->esquerda);
	imprimirPreOrdem(raiz->direita);
}

void desalloc(AVLno * raiz) {
	if(raiz == NULL) {
		return;
	}
	
	desalloc(raiz->esquerda);
	desalloc(raiz->direita);
	
	free(raiz);
}



int main() {
	AVLno * arvoreAVL;
	
	int numeroLido, arvoreIniciou = 0;
	while(scanf("%d", &numeroLido) == 1) {
		if(arvoreIniciou) {
			arvoreAVL = inserirNaAVL(arvoreAVL, numeroLido);
		} else {
			arvoreAVL = criarNo(numeroLido);
			arvoreIniciou = 1;
		}
	}
	
	imprimirPreOrdem(arvoreAVL);
	desalloc(arvoreAVL);
	
	return 0;
}
