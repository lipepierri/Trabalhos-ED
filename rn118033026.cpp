#include <cstdio>



class RN_no {
public:
	RN_no * esq, * dir;
	int chave;
	char cor;
	
	//Contrutor
	RN_no(int chave) {
		this->chave = chave;
		
		esq = NULL, dir = NULL;
		cor = 'R'; //cores: rubro = r, negro = n
	}
	
	//print em pre-ordem
	void print_PRE() {
		printf("%d%c\n", chave, cor);
		
		if(esq != NULL) {
			esq->print_PRE();
		}
		
		if(dir != NULL) {
			dir->print_PRE();
		}
	}
	
	//rotacao a esquerda
	RN_no * rot_Esquerda() {
		RN_no * raiz = dir, * meio = dir->esq;
		
		raiz->esq = this;
		dir = meio;
		
		return raiz;
	}
	
	//rotacao a direita
	RN_no * rot_Direita() {
		RN_no * raiz = esq, * meio = esq->dir;
		
		raiz->dir = this;
		esq = meio;
		
		return raiz;
	}
	
	void trocar_Cor() {
		cor = 'R';
		
		dir->cor = 'N';
		esq->cor = 'N';
	}
	
	//insere o no e balanceia obedecendo a RN
	RN_no * inserir(int chave) {
		//insere recursivamente
		if(chave < this->chave) {
			if(esq == NULL) {
				esq = new RN_no(chave);
			} else {
				esq = esq->inserir(chave);
			}
		} else {
			if(dir == NULL) {
				dir = new RN_no(chave);
			} else {
				dir = dir->inserir(chave);
			}
		}
		
		//se a cor for vermelho
		if(cor == 'R') {
			return this;
		}
		
		char dircor, esqcor;
		
		//define a cor do pai e do tio
		if(dir == NULL) {
			dircor = 'N';
		} else {
			dircor = dir->cor;
		}
		
		if(esq == NULL) {
			esqcor = 'N';
		} else {
			esqcor = esq->cor;
		}
		
		if(dircor == 'N' && esqcor == 'N') {
			return this;
		}
		
		//descobre onde o no filho esta
		
		//pai esquerdo
		if(chave < this->chave) {
			if(esqcor == 'N') {
				return this;
			}
			
			//esq esq
			if(chave < esq->chave) {
				if(esq->esq->cor == 'R') {
					if(dircor == 'N') {
						cor = 'R';
						esq->cor = 'N';
						
						return rot_Direita();
					} else {
						trocar_Cor();
						
						return this;
					}
				} else {
					return this;
				}
			}
			
			//esq dir
			if(esq->dir != NULL) {
				if(esq->dir->cor == 'R') {
					if(dircor == 'N') {
						esq = esq->rot_Esquerda();
						
						cor = 'R';
						esq->cor = 'N';
						
						return rot_Direita();
					} else {
						trocar_Cor();
						
						return this;
					}
				} else {
					return this;
				}
			} else {
				return this;
			}
		}
		
		//pai direito
		if(dircor == 'N') {
			return this;
		}
		
		//dir esq
		if(chave < dir->chave) {
			if(dir->esq->cor == 'R') {
				if(esqcor == 'N') {
					dir = dir->rot_Direita();
					
					cor = 'R';
					dir->cor = 'N';
					
					return rot_Esquerda();
				} else {
					trocar_Cor();
					
					return this;
				}
			} else {
				return this;
			}
		}
		
		//dir dir
		if(dir->dir != NULL) {
			if(dir->dir->cor == 'R') {
				if(esqcor == 'N') {
					cor = 'R';
					dir->cor = 'N';
					
					return rot_Esquerda();
				} else {
					trocar_Cor();
					
					return this;
				}
			} else {
				return this;
			}
		} else {
			return this;
		}
		
		printf("erro do fim\n");
	}
	
	//destroi a arvore toda
	void destruirArvore() {
		if(esq != NULL) {
			esq->destruirArvore();
		}
		if(dir != NULL) {
			dir->destruirArvore();
		}
		
		delete this;
	}
};



int main() {
	int chave;
	RN_no * raiz = NULL;
	
	while(scanf("%d", &chave) != EOF) {
		if(raiz == NULL) {
			raiz = new RN_no(chave);
		} else {
			raiz = raiz->inserir(chave);
		}
		
		raiz->cor = 'N';
	}
	
	raiz->print_PRE();
	raiz->destruirArvore();
	
	return 0;
}
