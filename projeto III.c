#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tech_store.h"

#define MAX_STRING_LENGTH 80

UsuarioList usuarios;
ProdutoList produtos;

void inicializarUsuarios() {
    usuarios.head = NULL;
    usuarios.size = 0;
}

void inicializarProdutos() {
    produtos.head = NULL;
    produtos.size = 0;
}

void mensagemBoasVindas() {
    printf("Xx===Bem-vindo a TECH - Loja de informatica!===xX\n");
}

int realizarLogin() {
    char nome_usuario[MAX_STRING_LENGTH];
    char senha[MAX_STRING_LENGTH];

    printf("Nome de usuario: ");
    scanf("%s", nome_usuario);
    printf("Senha: ");
    scanf("%s", senha);

    UsuarioNode *current = usuarios.head;
    while (current != NULL) {
        if (strcmp(nome_usuario, current->nome_usuario) == 0 && strcmp(senha, current->senha) == 0) {
            printf("Login bem-sucedido!\n");
            return 1;
        }
        current = current->next;
    }
    printf("Nome de usuario ou senha incorretos.\n");
    return 0;
}
void cadastrarUsuario() {
    UsuarioNode *novoUsuario = (UsuarioNode *)malloc(sizeof(UsuarioNode));
    if (novoUsuario == NULL) {
        printf("Erro ao alocar memoria para novo usuario.\n");
        return;
    }

    printf("Informe o nome do usuario:\n");
    scanf("%s", novoUsuario->nome_usuario);

    while (getchar() != '\n'); 

    printf("Informe a senha do usuario:\n");
    scanf("%s", novoUsuario->senha);

    while (getchar() != '\n'); 

    char buffer[MAX_STRING_LENGTH];
    do {
        printf("Informe o email do usuario:\n");
        fgets(buffer, MAX_STRING_LENGTH, stdin);
        strcpy(novoUsuario->email, strtok(buffer, "\n")); 
        if (strchr(novoUsuario->email, '@') == NULL) {
            printf("O email deve conter o caractere '@'. Por favor, insira um email valido.\n");
        }
    } while (strchr(novoUsuario->email, '@') == NULL);

    novoUsuario->next = usuarios.head;
    usuarios.head = novoUsuario;
    usuarios.size++;

    printf("Usuario cadastrado com sucesso!\n");
}

void salvarUsuarios(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    UsuarioNode *current = usuarios.head;
    while (current != NULL) {
        fwrite(current, sizeof(UsuarioNode), 1, arquivo);
        current = current->next;
    }

    fclose(arquivo);
}

void carregarUsuarios(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return;
    }

    UsuarioNode novoUsuario; 
    while (fread(&novoUsuario, sizeof(UsuarioNode), 1, arquivo)) { 
        UsuarioNode *novoUsuarioPtr = (UsuarioNode *)malloc(sizeof(UsuarioNode)); 
        if (novoUsuarioPtr == NULL) {
            printf("Erro ao alocar memória para novo usuário.\n");
            fclose(arquivo); 
            return;
        }
        *novoUsuarioPtr = novoUsuario; 
        novoUsuarioPtr->next = usuarios.head;
        usuarios.head = novoUsuarioPtr;
        usuarios.size++;
    }

    fclose(arquivo);
}


void cadastrarProduto() {
    ProdutoNode *novoProduto = (ProdutoNode *)malloc(sizeof(ProdutoNode));
    if (novoProduto == NULL) {
        printf("Erro ao alocar memoria para novo produto.\n");
        return;
    }

    printf("Informe o codigo, nome e preco do produto:\n");
    scanf("%d %s %f", &novoProduto->codigo, novoProduto->nome, &novoProduto->preco);

    novoProduto->next = produtos.head;
    produtos.head = novoProduto;
    produtos.size++;

    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    printf("Produtos cadastrados:\n");
    while (current != NULL) {
        printf("Codigo: %d | Nome: %s | Preco: %.2f\n", current->codigo, current->nome, current->preco);
        current = current->next;
    }
}

void buscarProduto(int codigo) {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    while (current != NULL) {
        if (current->codigo == codigo) {
            printf("Produto encontrado:\n");
            printf("Codigo: %d | Nome: %s | Preco: %.2f\n", current->codigo, current->nome, current->preco);
            return;
        }
        current = current->next;
    }
    printf("Produto nao encontrado.\n");
}

void editarProduto(int codigo) {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    while (current != NULL) {
        if (current->codigo == codigo) {
            printf("Informe o novo nome e preco do produto:\n");
            scanf("%s %f", current->nome, &current->preco);
            printf("Produto editado com sucesso!\n");
            return;
        }
        current = current->next;
    }
    printf("Produto nao encontrado.\n");
}

void excluirProduto(int codigo) {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *prev = NULL;
    ProdutoNode *current = produtos.head;
    while (current != NULL) {
        if (current->codigo == codigo) {
            if (prev == NULL) {
                produtos.head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            produtos.size--;
            printf("Produto excluido com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Produto nao encontrado.\n");
}

void listarProdutosPorPreco(int ascendente) {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    ProdutoNode *prev = NULL;
    ProdutoNode *temp = NULL;

    int swapped;
    do {
        swapped = 0;
        current = produtos.head;
        while (current->next != prev) {
            if ((ascendente && current->preco > current->next->preco) ||
                (!ascendente && current->preco < current->next->preco)) {
                float precoTemp = current->preco;
                current->preco = current->next->preco;
                current->next->preco = precoTemp;

                char nomeTemp[MAX_STRING_LENGTH];
                strcpy(nomeTemp, current->nome);
                strcpy(current->nome, current->next->nome);
                strcpy(current->next->nome, nomeTemp);

                int codigoTemp = current->codigo;
                current->codigo = current->next->codigo;
                current->next->codigo = codigoTemp;

                swapped = 1;
            }
            current = current->next;
        }
        prev = temp;
    } while (swapped);

    printf("Produtos ordenados por preco %s:\n", ascendente ? "crescente" : "decrescente");
    listarProdutos();
}

void listarProdutosPorNome() {
    if (produtos.size == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    ProdutoNode *prev = NULL;
    ProdutoNode *temp = NULL;

    int swapped;
    do {
        swapped = 0;
        current = produtos.head;
        while (current->next != prev) {
            if (strcmp(current->nome, current->next->nome) > 0) {
                float precoTemp = current->preco;
                current->preco = current->next->preco;
                current->next->preco = precoTemp;

                char nomeTemp[MAX_STRING_LENGTH];
                strcpy(nomeTemp, current->nome);
                strcpy(current->nome, current->next->nome);
                strcpy(current->next->nome, nomeTemp);

                int codigoTemp = current->codigo;
                current->codigo = current->next->codigo;
                current->next->codigo = codigoTemp;

                swapped = 1;
            }
            current = current->next;
        }
        prev = temp;
    } while (swapped);

    printf("Produtos ordenados por nome em ordem alfabetica:\n");
    listarProdutos();
}

void salvarProdutos(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    ProdutoNode *current = produtos.head;
    while (current != NULL) {
        fwrite(current, sizeof(ProdutoNode), 1, arquivo);
        current = current->next;
    }

    fclose(arquivo);
}

void carregarProdutos(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return;
    }

    ProdutoNode novoProduto; 
    while (fread(&novoProduto, sizeof(ProdutoNode), 1, arquivo)) { 
        ProdutoNode *novoProdutoPtr = (ProdutoNode *)malloc(sizeof(ProdutoNode)); 
        if (novoProdutoPtr == NULL) {
            printf("Erro ao alocar memória para novo produto.\n");
            fclose(arquivo); 
            return;
        }
        *novoProdutoPtr = novoProduto; 
        novoProdutoPtr->next = produtos.head;
        produtos.head = novoProdutoPtr;
        produtos.size++;
    }

    fclose(arquivo);
}

