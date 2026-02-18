// Modulo: fila.c
// Implementação da estrutura de dados Fila .
// Utilizada para organizar os clientes por ordem de chegada no atendimento.

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Fun��o: filaInit
// Inicializa a fila deixando ponteiros nulos e tamanho zero.
void filaInit(Fila *f) {
    f->ini = NULL;  // Início da fila
    f->fim = NULL;  // Final da fila
    f->tam = 0;     // Quantidade de elementos
}

// Função: filaVazia
// Verifica se a fila esta vazia.
// Retorna 1 se vazia, 0 caso contrário.
int filaVazia(Fila *f) {
    return (f->ini == NULL);
}

// Função: filaEnfileirar
// Insere um novo cliente no final da fila.
// Mantém a regra FIFO (ordem de chegada).
// Retorna 1 se sucesso, 0 se falha na alocação.

int filaEnfileirar(Fila *f, int idCliente) {
    for(int i = 0; i < f->tam; i++) { // Verifica se o cliente ja este na fila 
        if(f->ini->idCliente == idCliente) {
            return 0;
        }
        f->ini = f->ini->prox;
    }
    // Aloca memória para novo nó da fila
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if(!novo) return 0; // Falha na alocação

    novo->idCliente = idCliente;
    novo->prox = NULL; // Sempre entra no final, então não aponta para ninguém

    // Se a fila estiver vazia, incio e fim apontam para o novo n
    if(f->fim == NULL) {
        f->ini = f->fim = novo;
    }
    // Caso contrário, adiciona no final e atualiza ponteiro fim
    else {
        f->fim->prox = novo;
        f->fim = novo;
    }

    f->tam++; // Incrementa tamanho da fila
    return 1;
}

// Função: filaDesenfileirar
// Remove o primeiro elemento da fila (ordem FIFO).
// Retorna o ID removido através do ponteiro idOut.
// Retorna 1 se sucesso, 0 se fila vazia.
int filaDesenfileirar(Fila *f, int *idOut) {

    // Verifica se a fila esta vazia
    if(filaVazia(f)) return 0;

    // Guarda o primeiro nó
    NoFila *temp = f->ini;

    // Se o ponteiro de saída for válido, retorna o ID removido
    if(idOut)
        *idOut = temp->idCliente;

    // Avança o início da fila
    f->ini = f->ini->prox;

    // Se a fila ficou vazia, o fim também deve ser NULL
    if(f->ini == NULL)
        f->fim = NULL;

    free(temp); // Libera memória do nó removido
    f->tam--;   // Decrementa tamanho da fila

    return 1;
}

// Função: filaTamanho
// Retorna a quantidade atual de elementos na fila.
int filaTamanho(Fila *f) {
    return f->tam;
}

