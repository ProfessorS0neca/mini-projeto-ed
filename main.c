// Arquivo principal do sistema de livraria
// Responsável por iniciar as estruturas e controlar o menu principal.
// Estruturas utilizadas no sistema:
// - Lista encadeada (livros e clientes)
// - Fila (controle de atendimento - FIFO)
// - Pilha (historico de vendas - LIFO)
// - Array (relatorios)

#include <stdio.h>
#include "livro.c"
#include "cliente.c"
#include "fila.c"
#include "pilha.c"
#include "venda.c"
#include "relatorio.c"

int main() {

    // Ponteiros das listas encadeadas principais
    Livro *livros = NULL;
    Cliente *clientes = NULL;

    // Inicializacao da fila de atendimento
    Fila fila;
    filaInit(&fila);

    // Inicializacao da pilha de historico de vendas
    Pilha historico;
    pilhaInit(&historico);

    int op;

    // Menu principal do sistema
    do {
        printf("\n==== LIVRARIA ====\n");
        printf("1 - Cadastros\n");
        printf("2 - Fila (entrar / atender)\n");
        printf("3 - Relatorios\n");
        printf("4 - Historico\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                menuCadastros(&livros, &clientes);
                break;

            case 2:
                menuFila(&fila, clientes, livros, &historico);
                break;

            case 3:
                menuRelatorios(livros);
                break;

            case 4:
                menuHistorico(&historico, livros);
                break;
        }

    } while(op != 0);

    return 0;
}
