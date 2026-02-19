#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct Cliente {
    int id;
    char nome[50];
    struct Cliente *prox;
} Cliente;

Cliente* clienteBuscar(Cliente *lista, int id);
void clienteListar(Cliente *lista);
void clienteInserir(Cliente **lista);
void removerCliente(Cliente **lista, int id);

#endif


