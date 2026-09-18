#include <stdio.h>
#include "arvore.h"

// Código principal
int main()
{
    printf("\nÁrvore Binária de Busca (Palavras)\n\n");
    Nodo* raiz = NULL;

    // Inserindo valores de teste diretamente como strings
    raiz = Inserir(raiz, "Alfa");
    raiz = Inserir(raiz, "B");
    raiz = Inserir(raiz, "C");
    raiz = Inserir(raiz, "D");
    raiz = Inserir(raiz, "E");
    raiz = Inserir(raiz, "F");
    raiz = Inserir(raiz, "G");
    raiz = Inserir(raiz, "H");
    raiz = Inserir(raiz, "I");
    raiz = Inserir(raiz, "J");
    raiz = Inserir(raiz, "K");
    raiz = Inserir(raiz, "L");
    raiz = Inserir(raiz, "M");
    raiz = Inserir(raiz, "N");
    raiz = Inserir(raiz, "O");
    raiz = Inserir(raiz, "P");
    raiz = Inserir(raiz, "Q");
    raiz = Inserir(raiz, "R");
    raiz = Inserir(raiz, "S");
    raiz = Inserir(raiz, "T");
    raiz = Inserir(raiz, "U");
    raiz = Inserir(raiz, "V");
    raiz = Inserir(raiz, "W");
    raiz = Inserir(raiz, "X");
    raiz = Inserir(raiz, "Y");
    raiz = Inserir(raiz, "Z");
    printf("Caminhamento Em-Ordem: ");
    EmOrdem(raiz);
    printf("\n\n");

    // Teste de busca
    const char *busca = "M";
    if (BuscarIterativo(raiz, busca) != NULL) {
        printf("Letra: %s encontrado na arvore!\n", busca);
    } else {
        printf("Letra: %s nao encontrado.\n", busca);
    }

    // Teste de remoção
    printf("\nRemovendo o valor 'H'...\n");
    raiz = remover(raiz, "H");
    printf("Em-Ordem apos remocao: ");
    EmOrdem(raiz);
    printf("\n\n");
    return 0;
}
