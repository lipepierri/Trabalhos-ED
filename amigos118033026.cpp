#import <stdio.h>
#import <stdlib.h>

#define TAMANHO 30

typedef struct elemento{
  struct elemento * conjunto;
  int rank;
  int tamanho;
} Elemento;

Elemento criando_elemento(Elemento * raizDoGrupo);

Elemento* busca(int indice, Elemento * lista_elementos);

void uniao(int indice_1, int indice_2, Elemento * lista_elementos);

void maior_tamanho(Elemento * lista_elementos, int numero_elementos_usados);

int main(){
  int numero_elementos_usados, i=0, primeiro_elemento, segundo_elemento;
  char * armazenador;
  armazenador = (char*)malloc(sizeof(char)*TAMANHO);

  scanf("%d", &numero_elementos_usados);
  Elemento * lista_elementos = (Elemento*)malloc(sizeof(Elemento)*numero_elementos_usados);

  while (i < numero_elementos_usados){
    lista_elementos[i] = criando_elemento(&lista_elementos[i]);
    i++;
  }

  while (!feof(stdin)){
    if ((scanf("%s", armazenador)) <= 0)
        return 0;

    if (armazenador[0] == '?'){
      maior_tamanho(lista_elementos, numero_elementos_usados);
      armazenador[0] = '\0';

    } else {
      primeiro_elemento = atoi(armazenador);
      scanf("%d", &segundo_elemento);
      uniao(primeiro_elemento-1, segundo_elemento-1, lista_elementos);
    }
  }
  return 0;
}

void maior_tamanho(Elemento * lista_elementos, int numero_elementos_usados){
  int tamanho_maior_grupo=0, i=0;

  while (i < numero_elementos_usados){
    if (lista_elementos[i].tamanho > tamanho_maior_grupo){
      tamanho_maior_grupo = lista_elementos[i].tamanho;
    }
    i++;
  }
  printf("%d\n", tamanho_maior_grupo);
}

Elemento criando_elemento(Elemento * raizDoGrupo){
  Elemento elemento;
  elemento.rank = 0;
  elemento.tamanho = 1;
  elemento.conjunto = raizDoGrupo;
  return elemento;
}

void uniao(int indice_1, int indice_2, Elemento * lista_elementos){

  Elemento * primeiro_conjunto = busca(indice_1, lista_elementos);
  Elemento * segundo_conjunto = busca(indice_2, lista_elementos);

  if (primeiro_conjunto == segundo_conjunto){
    return;
  }
  if (primeiro_conjunto->rank < segundo_conjunto->rank){
    primeiro_conjunto->conjunto = segundo_conjunto;
    segundo_conjunto->tamanho += primeiro_conjunto->tamanho;
  } else
  if (primeiro_conjunto->rank == segundo_conjunto->rank){
    primeiro_conjunto->conjunto = segundo_conjunto;
    segundo_conjunto->rank++;
    segundo_conjunto->tamanho += primeiro_conjunto->tamanho;
  } else {
    segundo_conjunto->conjunto = primeiro_conjunto;
    primeiro_conjunto->tamanho += segundo_conjunto->tamanho;
  }
  return;
}

Elemento* busca(int indice, Elemento * lista_elementos){

  Elemento * elemento = lista_elementos + indice;

  while (elemento->conjunto != elemento){
    elemento = elemento->conjunto;
  }

  return elemento;
}
