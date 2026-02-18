#ifndef PILHA_H
#define PILHA_H

typedef struct RegistroVenda {
    int idCliente;
    int idLivro;
    int qtd;
    float total;
    char nomeLivro[50];
    struct RegistroVenda *prox;
} RegistroVenda;

typedef struct Pilha {
    RegistroVenda *topo;
    int tam;
} Pilha;

void pilhaInit(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaPush(Pilha *p, RegistroVenda reg);
int pilhaPop(Pilha *p, RegistroVenda *out);
void pilhaMostrar(Pilha *p);
int pilhaTamanho(Pilha *p);

#endif

