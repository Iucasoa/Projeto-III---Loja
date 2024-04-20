#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tech_store.h"

UsuarioList usuarios;
ProdutoList produtos;

int main() {
    inicializarUsuarios();
    inicializarProdutos();

    mensagemBoasVindas();

    carregarUsuarios("usuarios.dat");
    carregarProdutos("produtos.dat");

    int opcao;
    int login_sucesso = 0;

    do {
        if (!login_sucesso) {
            printf("=================================\n");
            printf("Escolha uma opcao:\n");
            printf("1 - Realizar login\n");
            printf("2 - Cadastrar usuario\n");
            printf("3 - Listar produtos\n");
            printf("4 - Buscar produto\n");
            printf("0 - Sair\n");
            printf("=================================\n");
        } else {
            printf("=================================\n");
            printf("Menu de Opcoes de Produto:\n");
            printf("1 - Cadastrar produto\n");
            printf("2 - Editar produto\n");
            printf("3 - Buscar produto\n");
            printf("4 - Listar produtos\n");
            printf("5 - Listar produtos por ordem crescente de preco\n");
            printf("6 - Listar produtos por ordem decrescente de preco\n");
            printf("7 - Listar produtos por ordem alfabetica\n");
            printf("8 - Excluir produto\n");            
            printf("0 - Sair\n");
            printf("=================================\n");
        }

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!login_sucesso) {
                    login_sucesso = realizarLogin();
                } else {
                    cadastrarProduto();
                }
                break;
            case 2:
                if (!login_sucesso) {
                    cadastrarUsuario();
                } else {
                    int codigo;
                    printf("Informe o codigo do produto a ser editado:\n");
                    scanf("%d", &codigo);
                    editarProduto(codigo);
                }
                break;
            case 3:
                if (!login_sucesso) {
                    listarProdutos();
                } else {
                    int codigo;
                    printf("Informe o codigo do produto:\n");
                    scanf("%d", &codigo);
                    buscarProduto(codigo);
                }
                break;
            case 4:
                listarProdutos();
                break;
            case 5:
                listarProdutosPorPreco(1);
                break;
            case 6:
                listarProdutosPorPreco(0);
                break;
            case 7:
                listarProdutosPorNome();
                break;
            case 8:
                if (!login_sucesso) {
                    printf("Você precisa estar logado para excluir um produto.\n");
                } else {
                    int codigo;
                    printf("Informe o codigo do produto a ser excluido:\n");
                    scanf("%d", &codigo);
                    excluirProduto(codigo);
                }
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    salvarUsuarios("usuarios.dat");
    salvarProdutos("produtos.dat");

    ProdutoNode *currentProduto = produtos.head;
    while (currentProduto != NULL) {
        ProdutoNode *temp = currentProduto;
        currentProduto = currentProduto->next;
        free(temp);
    }

    UsuarioNode *currentUsuario = usuarios.head;
    while (currentUsuario != NULL) {
        UsuarioNode *temp = currentUsuario;
        currentUsuario = currentUsuario->next;
        free(temp);
    }

    return 0;
}
