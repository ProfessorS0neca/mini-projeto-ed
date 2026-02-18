// Módulo: relatorio.c
// Responsável por exibir relatórios do sistema.
// Aqui utilizamos:
// - Percurso em lista encadeada (para encontrar top livro)

#include <stdio.h>
#include <string.h>
#include "relatorio.h"

// Função: menuRelatorios
// Exibe um submenu com relatórios do sistema.
// Relatórios disponíveis:
// 1) Top livro (maior vendidos)
void menuRelatorios(Livro *livros) {

    int op;

    do {
        printf("\n=== RELATORIOS ===\n");
        printf("1 - Top livro\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &op);

        // Opção 1: encontra o livro mais vendido
        if(op == 1) {

            Livro *top = NULL; // aponta para o livro mais vendido
            Livro *p = livros;

            // Percorre a lista comparando o campo 'vendidos'
            while(p != NULL) {
                if(top == NULL || p->vendidos > top->vendidos)
                    top = p;
                p = p->prox;
            }

            if(top)
                printf("Top livro: %s (vendidos: %d)\n", top->nome, top->vendidos);
            else
                printf("Sem livros.\n");
        }

    } while(op != 0); // sai quando o usuário escolher 0
}
