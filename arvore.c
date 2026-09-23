/******************************************************************************
Árvore Binária de Busca - Organizada pelo alfabeto
Implementação das funções
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

// Criação de um nó da árvore.
// Nodo* vem antes da função porque o retorno é ponteiro(IMPORTANTE).
Nodo* CriarNo(const char *valor)
{
    Nodo* novoNo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    strcpy(novoNo->valor, valor);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    // Todo novo nó começa com altura 1
    novoNo->altura = 1;
    return novoNo;
}

// OBTER ALTURA
int Obter_altura(Nodo* No)
{
    if (No == NULL) {
        return 0;
    }
    return No->altura;
}

// Calcular o Maior Valor
int Maior_Valor(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

// Fator de Balanceamento
int Fator_de_Balancemento(Nodo* No)
{
    if (No == NULL) {
        return 0;
    }
    int FB = Obter_altura(No->esquerda)
           - Obter_altura(No->direita);
    return FB;
}

// Função auxiliar para comparar duas palavras
// Critério: Ordem Alfabética
int Comparar(const char *a, const char *b)
{
    return strcmp(a, b);
}

// Colocar algum valor dentro da raiz
Nodo* Inserir(Nodo* raiz, const char *valor)
{
    // Se a árvore estiver vazia
    if (raiz == NULL) {
        return CriarNo(valor);
    }
    int comp = Comparar(valor, raiz->valor);

    // Valor menor -> esquerda
    if (comp < 0) {
        raiz->esquerda = Inserir(raiz->esquerda, valor);
    }
    // Valor maior -> direita
    else if (comp > 0) {
        raiz->direita = Inserir(raiz->direita, valor);
    }
    // Valor igual -> não inserir duplicado
    else {
        return raiz;
    }
    int FB = Fator_de_Balancemento(raiz);

	// Esquerda para esquerda.
	if(FB > 1 && Fator_de_Balancemento(raiz->esquerda) >=0){
		return Rotacaoadireita(raiz);
	}

	// Esquerda para direita.
	if(FB > 1 && Fator_de_Balancemento(raiz->esquerda)< 0){
		raiz->esquerda = Rotacaoaesquerda(raiz->esquerda);
		return Rotacaoadireita(raiz);
	}

	// Direita para direita.
	if(FB < -1 && Fator_de_Balancemento(raiz->direita)<=0){
		return Rotacaoaesquerda(raiz);
	}

	// Direita para esquerda.
	if(FB < -1 && Fator_de_Balancemento(raiz->direita)>0){
		raiz->direita = Rotacaoadireita(raiz->direita);
		return Rotacaoaesquerda(raiz);
	}
	// Nenhum caso de rotação anterior então atualiza a altura aqui manualmente.
	raiz->altura = 1 + Maior_Valor(Obter_altura(raiz->esquerda), Obter_altura(raiz->direita));
	return raiz;
}

// Encontrando o nó com menor valor
// (mais à esquerda)
Nodo* Encontrar_Minimo(Nodo* No)
{
    Nodo* atual = No;
    while (atual != NULL && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Encontrando o nó com maior valor
// (mais à direita)
Nodo* ENcontrar_Maximo(Nodo* No)
{
    Nodo* atual = No;
    while (atual != NULL && atual->direita != NULL) {
        atual = atual->direita;
    }
    return atual;
}

// Remoção de um nó
Nodo* remover(Nodo* raiz, const char *valor)
{
    if (raiz == NULL) {
        return raiz;
    }
    Nodo* atual = raiz;
    Nodo* pai = NULL;

    // Encontrar o nó a ser removido
    while (
        atual != NULL &&
        strcmp(atual->valor, valor) != 0
    ) {
        pai = atual;
        if (Comparar(valor, atual->valor) < 0) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    // Não encontrado
    if (atual == NULL) {
        return raiz;
    }

    // Caso 1: Nó folha
    if (
        atual->esquerda == NULL &&
        atual->direita == NULL
    ) {
        if (atual != raiz) {
            if (pai->esquerda == atual) {
                pai->esquerda = NULL;
            } else {
                pai->direita = NULL;
            }
        } else {
            raiz = NULL;
        }
        free(atual);
    }
    // Caso 2: Nó com um filho
    else if (
        atual->esquerda == NULL ||
        atual->direita == NULL
    ) {
        Nodo* filho;
        if (atual->esquerda != NULL) {
            filho = atual->esquerda;
        } else {
            filho = atual->direita;
        }
        if (atual != raiz) {
            if (atual == pai->esquerda) {
                pai->esquerda = filho;
            } else {
                pai->direita = filho;
            }
        } else {
            raiz = filho;
        }
        free(atual);
    }
    // Caso 3: Nó com dois filhos
    else {
        Nodo* sucessorPai = atual;
        Nodo* sucessor = atual->direita;

        // Encontrar o menor valor da subárvore direita
        while (sucessor->esquerda != NULL) {
            sucessorPai = sucessor;
            sucessor = sucessor->esquerda;
        }
        if (sucessorPai != atual) {
            sucessorPai->esquerda = sucessor->direita;
        } else {
            sucessorPai->direita = sucessor->direita;
        }
        // Copiar o valor do sucessor
        strcpy(atual->valor, sucessor->valor);
        free(sucessor);
    }
    return raiz;
}

Nodo* Rotacaoadireita(Nodo* No){
// No da funcao igual C ----^.
/*	    C */	Nodo* raiznova = No->esquerda;
//     /	    RaizNova = B.
/*    B   */	No->esquerda = raiznova->direita;
//   /	 	    C->esquerda = B->direita.
/*  A     */	raiznova->direita = No;
//Vira		    C->direita = B.
/*   B    */	No->altura = 1 + Maior_Valor(Obter_altura(No->esquerda), Obter_altura(No->direita));
//  / \		    recalcula altura de C que "desceu", então precisa atualizar primeiro.
/* A   C  */	raiznova->altura = 1 + Maior_Valor(Obter_altura(raiznova->esquerda), Obter_altura(raiznova->direita));
//Desenhei	    recalcula altura de B que "subiu", depende da altura de C esteja atualizada.
/*para entender*/ printf("Rotacao Direita: %s virou raiz | Altura: %d | FB: %d\n",raiznova->valor, raiznova->altura, Fator_de_Balancemento(raiznova));
				return raiznova; // Return B.
}

Nodo* Rotacaoaesquerda(Nodo* No){
	Nodo* raiznova = No->direita;
	No->direita = raiznova->esquerda;
	raiznova->esquerda = No;
	No->altura = 1 + Maior_Valor(Obter_altura(No->esquerda), Obter_altura(No->direita));
	raiznova->altura = 1 + Maior_Valor(Obter_altura(raiznova->esquerda), Obter_altura(raiznova->direita));
	printf("Rotacao Esquerda: %s virou raiz | Altura: %d | FB: %d\n",raiznova->valor, raiznova->altura, Fator_de_Balancemento(raiznova));
	return raiznova;
}

// Busca Iterativa
Nodo* BuscarIterativo(Nodo* raiz, const char *valor)
{
    Nodo* atual = raiz;
    while (atual != NULL) {
        int comp = Comparar(valor, atual->valor);
        if (comp == 0) {
            return atual;
        }
        if (comp < 0) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;

        }
    }
    return NULL;
}


// Percurso Em-Ordem
void EmOrdem(Nodo* raiz)
{
    if (raiz != NULL) {
        EmOrdem(raiz->esquerda);
        printf("[%s] ", raiz->valor);
        EmOrdem(raiz->direita);
    }
}

Nodo* Lerarquivo(Nodo* raiz, const char *vasculhar){
	FILE* arquivo = fopen(vasculhar, "r");
	if (arquivo == NULL){
		printf("Erro em abrir o arquivo\n");
		return raiz;
	}
	char linha[50];
	int contador =0;
	while(fgets(linha, sizeof(linha), arquivo) != NULL){
	//Cuidado que tem o \n junto(Lembrete).
	size_t tamanho = strlen(linha);
		if(tamanho > 0 && linha[tamanho -1] =='\n'){
			linha[tamanho -1] ='\0';
			// Substitui o \n para \0.
		}
		// If para ignorar linhas vazias.
		if(strlen(linha)>0){
			raiz = Inserir (raiz, linha);
			contador++;
		}
	}
	fclose(arquivo);
	printf("%d palavras carregadas do arquivo '%s'.\n", contador, vasculhar);
    return raiz;
}

void ImprimirNivel(Nodo* raiz, int nivel){
	if(raiz==NULL){
		return;
	}
	if(nivel==0){
		printf("%s", raiz->valor);
	}else{
		ImprimirNivel(raiz->esquerda, nivel -1);
		ImprimirNivel(raiz->direita, nivel -1);
	}
}

void ImprimirPorNiveis(Nodo* raiz){
	if(raiz == NULL){
		printf("Arvore binaria está vazia\n");
		return;
	}
	int altura = Obter_altura(raiz);
	for(int nivel =0; nivel < altura; nivel++){
		printf("Nivel %d: ", nivel);
        ImprimirNivel(raiz, nivel);
        printf("\n");

	}
}

void Imprimirarvore(Nodo* raiz, int espaco){
    const int DEsenho = 8;
    if (raiz == NULL) {
        return;
    }
    espaco += DEsenho;
    // Desenha lado direito (aparece mais acima na tela)
    Imprimirarvore(raiz->direita, espaco);
    printf("\n");
    for (int i = DEsenho; i < espaco; i++) {
        printf(" ");
    }
    printf("%s\n", raiz->valor);
    // Desenha lado esquerdo
    Imprimirarvore(raiz->esquerda, espaco);
}
