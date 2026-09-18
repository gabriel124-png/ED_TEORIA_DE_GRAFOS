#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Struct para os nós da árvore
typedef struct Node {
    char valor[50];
    struct Node* esquerda;
    struct Node* direita;
    int altura;
} Nodo;

// Protótipos das Funções

// Criar Nó
Nodo* CriarNo(const char *valor);

// Funções para o Balanceamento
int Obter_altura(Nodo* No);
int Maior_Valor(int a, int b);
int Fator_de_Balancemento(Nodo* No);

// Árvore como um todo
int Comparar(const char *a, const char *b);
Nodo* Inserir(Nodo* raiz, const char *valor);
Nodo* Encontrar_Minimo(Nodo* No);
Nodo* ENcontrar_Maximo(Nodo* No);
Nodo* remover(Nodo* raiz, const char *valor);
Nodo* BuscarIterativo(Nodo* raiz, const char *valor);
void EmOrdem(Nodo* raiz);

#endif
