#ifndef VENDA_H
#define VENDA_H

#include "livro.h"
#include "cliente.h"
#include "fila.h"
#include "pilha.h"

void menuCadastros(Livro **livros, Cliente **clientes);
void menuFila(Fila *fila, Cliente *clientes, Livro *livros, Pilha *historico);
void menuHistorico(Pilha *historico, Livro *livros);

#endif
