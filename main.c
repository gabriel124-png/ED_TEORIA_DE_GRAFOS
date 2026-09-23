#include <stdio.h>
#include <string.h>
#include "arvore.h"

#define arquivo "arquivo/palavras.txt"

// Código principal
int main(){
    int op = 0;
	Nodo* raiz=NULL;
	raiz = Lerarquivo(raiz, arquivo);
    do{
        printf("\n1-Imprimir a Arvore Binaria de Busca(Já vem pre-montada)\n");
        printf("2-Adicione uma palavra\n");
        printf("3-Buscar uma palavra\n");
        printf("4-Remover uma palavra\n");
        printf("5-Imprimir Em-Ordem\n");
        printf("6-Mostrar a menor palavra\n");
        printf("7-Mostrar a maior palavra\n");
	printf("8-Ver a arvore como desenho (deitada)\n");
        printf("0-Presione 0(Zero) para sair\n");
        scanf("%d", &op);
        switch(op){

		case 1:
		ImprimirPorNiveis(raiz);
		break;
        	case 2:
        		char entrada[50];
                int con=1;
                do{
                	printf("Digite uma palavra para adicionar a Arvore Binaria de Busca\n");
                	// Sem & para arry de string(Importante).
                	scanf("%s", entrada);
                	raiz = Inserir(raiz, entrada);
                	printf("Deseja continuar escrevendo(qualquer número para continuar e 0 para sair)");
                	scanf("%d", &con);
                }while(con!=0);
        		break;
            case 3:
            {
                char busca[50];
                printf("Digite a palavra a buscar:\n");
                scanf("%s", busca);
                if (BuscarIterativo(raiz, busca) != NULL) {
                    printf("Palavra '%s' encontrada na arvore!\n", busca);
                } else {
                    printf("Palavra '%s' nao encontrada.\n", busca);
                }
            }
                break;
            case 4:
            {
                char aRemover[50];
                printf("Digite a palavra a remover:\n");
                scanf("%s", aRemover);
                if (BuscarIterativo(raiz, aRemover) != NULL) {
                    raiz = remover(raiz, aRemover);
                    printf("Palavra '%s' removida com sucesso.\n", aRemover);
                } else {
                    printf("Palavra '%s' nao encontrada na arvore. Nada foi removido.\n", aRemover);
                }
            }
                break;
            case 5:
                printf("Em-Ordem: ");
                EmOrdem(raiz);
                printf("\n");
                break;
            case 6:
            {
                Nodo* menor = Encontrar_Minimo(raiz);
                if (menor != NULL) {
                    printf("Menor palavra: %s\n", menor->valor);
                } else {
                    printf("Arvore vazia.\n");
                }
            }
                break;
            case 7:
            {
                Nodo* maior = ENcontrar_Maximo(raiz);
                if (maior != NULL) {
                    printf("Maior palavra: %s\n", maior->valor);
                } else {
                    printf("Arvore vazia.\n");
                }
            }
                break;
            case 0:
                printf("Saindo\n");
                break;
		case 8:
                printf("\n Imprimir Arvore\n");
                Imprimirarvore(raiz, 0);
                printf("\n");
            default:
                printf("nao tem\n");
                break;
        }
    }while(op != 0);
    return 0;
}
