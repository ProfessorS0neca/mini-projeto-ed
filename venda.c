// Módulo: venda.c
// Este módulo integra as principais estruturas do sistema:
// - Fila (FIFO): controla a ordem de atendimento dos clientes
// - Listas encadeadas: armazenam clientes e livros
// - Pilha (LIFO): registra o histórico de vendas e permite desfazer a última operação
// Também contém os submenus:
// - menuCadastros
// - menuFila (entrada na fila e atendimento/venda)
// - menuHistorico (mostrar e desfazer vendas)

#include <stdio.h>
#include <string.h>

#include "venda.h"
#include "livro.h"
#include "cliente.h"
#include "fila.h"
#include "pilha.h"

// Função interna (static): atenderProximo
// Remove o próximo cliente da fila e inicia o atendimento.
// Durante o atendimento o cliente pode comprar vários livros (loop).
// Cada compra realizada:
// - reduz estoque do livro
// - incrementa vendidos do livro
// - salva um RegistroVenda na pilha de histórico (para permitir desfazer)
static void atenderProximo(Fila *fila, Cliente *clientes, Livro *livros, Pilha *historico) {

    // 1) Pega o primeiro cliente da fila (FIFO)
    int idCliente;
    if(!filaDesenfileirar(fila, &idCliente)) {
        printf("Fila vazia!\n");
        return;
    }

    // 2) Busca o cliente na lista encadeada
    Cliente *c = clienteBuscar(clientes, idCliente);
    if(!c) {
        printf("Cliente nao existe!\n");
        return;
    }

    printf("\nCliente da vez: %s\n", c->nome);

    // 3) Loop de compras
    while(1) {
        int idLivro;
        printf("\nID do livro (0 para finalizar): ");
        scanf("%d", &idLivro);

        if(idLivro == 0) break;

        // 4) Busca o livro
        Livro *l = livroBuscar(livros, idLivro);
        if(!l) {
            printf("Livro nao existe!\n");
            continue;
        }

        // 5) Pergunta a quantidade desejada
        int qtd;
        printf("Quantidade: ");
        scanf("%d", &qtd);

        if(qtd <= 0 || l->quantidade < qtd) {
            printf("Quantidade invalida ou estoque insuficiente!\n");
            continue;
        }

        // 6) Atualiza dados do livro
        l->quantidade -= qtd;
        l->vendidos += qtd;

        // 7) Registro da venda (pilha)
        RegistroVenda reg;
        reg.idCliente = idCliente;
        reg.idLivro = idLivro;
        reg.qtd = qtd;
        reg.total = l->preco * qtd;

        strcpy(reg.nomeLivro, l->nome);

        pilhaPush(historico, reg);

        printf("Venda OK: %s x%d (R$%.2f)\n", l->nome, qtd, reg.total);
    }

    printf("Atendimento finalizado.\n");
}

static void entrarFila(Fila *fila, Cliente *clientes) {

    int id;
    printf("Digite o ID do cliente para entrar na fila (0 para parar): ");
    scanf("%d", &id);

    while(id != 0) {

        // 1) Verifica se o cliente existe
        if(!clienteBuscar(clientes, id)) {
            printf("Cliente nao cadastrado.\n");
        }
        // 2) Cliente existe → tenta colocar na fila
        else if(!filaEnfileirar(fila, id)) {
            printf("Cliente ja esta na fila.\n");
        }
        // 3) Entrou com sucesso
        else {
            printf("Cliente %d entrou na fila.\n", id);
        }

        printf("Digite o ID do cliente para entrar na fila (0 para parar): ");
        scanf("%d", &id);
    }
}


// Função: menuCadastros
void menuCadastros(Livro **livros, Cliente **clientes) {

    int op;
    do {
        printf("\n=== CADASTROS ===\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Livro\n");
        printf("3 - Listar tudo\n");
        printf("4 - Remover Cliente\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &op);

        if(op == 1)
            clienteInserir(clientes);

        else if(op == 2)
            cadastrarLivro(livros);

        else if(op == 3) {
            clienteListar(*clientes);
            livroListar(*livros);
        }
        else if(op == 4) {
            int id;
            printf("ID do cliente a remover: ");
            scanf("%d", &id);
            removerCliente(clientes, id);
        }

    } while(op != 0);
}

// Função: menuFila
void menuFila(Fila *fila, Cliente *clientes, Livro *livros, Pilha *historico) {

    int op;
    do {
        printf("\n=== (FILA FIFO) ===\n");
        printf("Aguardando: %d\n", filaTamanho(fila));
        printf("1 - Entrar na fila (Cliente)\n");
        printf("2 - Atender cliente (faz venda)\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &op);

        if(op == 1)
            entrarFila(fila, clientes);

        else if(op == 2)
            atenderProximo(fila, clientes, livros, historico);

    } while(op != 0);
}

// Função: menuHistorico
void menuHistorico(Pilha *historico, Livro *livros) {

    int op;
    do {
        printf("\n=== HISTORICO ===\n");
        printf("1 - Mostrar historico\n");
        printf("2 - Desfazer ultima venda\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &op);

        if(op == 1)
            pilhaMostrar(historico);

        else if(op == 2) {

            RegistroVenda reg;

            if(pilhaPop(historico, &reg)) {

                Livro *l = livroBuscar(livros, reg.idLivro);

                if(l) {
                    l->quantidade += reg.qtd;
                    l->vendidos -= reg.qtd;
                }

                printf("Desfeito: %s x%d\n", reg.nomeLivro, reg.qtd);

            } else {
                printf("Historico vazio.\n");
            }
        }

    } while(op != 0);
}
