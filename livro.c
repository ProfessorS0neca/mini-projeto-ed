// Módulo: livro.c
// Implementação da lista encadeada de livros.
// Permite buscar, listar e cadastrar livros no sistema.
// Tambm mantém controle de estoque e quantidade vendida.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

// Função: livroBuscar
// Percorre a lista encadeada procurando um livro pelo ID.
// Retorna ponteiro para o livro encontrado ou NULL se não existir.
Livro* livroBuscar(Livro *lista, int id) {
    while(lista != NULL) {
        if(lista->id == id)
            return lista; // Livro encontrado
        lista = lista->prox; // Avana para o prximo n
    }
    return NULL; // Livro no encontrado
}

// Função: livroListar
// Exibe todos os livros cadastrados no sistema.
void livroListar(Livro *lista) {

    printf("\n=== LIVROS ===\n");

    // Verifica se a lista esta vazia
    if(lista == NULL) {
        printf("(vazio)\n");
        return;
    }

    // Percorre toda a lista exibindo informações
    while(lista != NULL) {
        printf("ID:%d | %s | Genero:%s | Ano:%d | R$%.2f | Estoque:%d | Vendidos:%d\n",
               lista->id,
               lista->nome,
               lista->genero,
               lista->ano,
               lista->preco,
               lista->quantidade,
               lista->vendidos);

        lista = lista->prox;
    }
}

// Função: cadastrarLivro
// Insere um novo livro no inicio da lista encadeada.
// Tambm verifica se o ID j existe para evitar duplicidade.
void cadastrarLivro(Livro **lista) {

    // Aloca memória para novo livro
    Livro *novo = (Livro*) malloc(sizeof(Livro));
    if(!novo) return; // Falha na alocação

    printf("ID Livro: ");
    scanf("%d", &novo->id);

    // Verifica se já existe livro com mesmo ID
    if(livroBuscar(*lista, novo->id)) {
        printf("ID ja existe.\n");
        free(novo); // Libera memória se ID duplicado
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novo->nome);

    printf("Genero: ");
    scanf(" %[^\n]", novo->genero);

    printf("Ano: ");
    scanf("%d", &novo->ano);

    printf("Preco: ");
    scanf("%f", &novo->preco);

    printf("Quantidade: ");
    scanf("%d", &novo->quantidade);

    // Inicializa controle de vendas
    novo->vendidos = 0;

    // Inserção no inicio da lista (operação O(1))
    novo->prox = *lista;
    *lista = novo;

    printf("Livro cadastrado!\n");
}

