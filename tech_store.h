#ifndef TECH_STORE_H
#define TECH_STORE_H

#define MAX_STRING_LENGTH 80

typedef struct UsuarioNode {
    char nome_usuario[MAX_STRING_LENGTH];
    char senha[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    struct UsuarioNode *next;
} UsuarioNode;

typedef struct {
    UsuarioNode *head;
    int size;
} UsuarioList;

typedef struct ProdutoNode {
    int codigo;
    char nome[MAX_STRING_LENGTH];
    float preco;
    struct ProdutoNode *next;
} ProdutoNode;

typedef struct {
    ProdutoNode *head;
    int size;
} ProdutoList;

void inicializarUsuarios();
void inicializarProdutos();
void mensagemBoasVindas();
int realizarLogin();
void cadastrarUsuario();
void salvarUsuarios(const char *nome_arquivo);
void carregarUsuarios(const char *nome_arquivo);
void cadastrarProduto();
void listarProdutos();
void buscarProduto(int codigo);
void editarProduto(int codigo);
void excluirProduto(int codigo);
void listarProdutosPorPreco(int ascendente);
void listarProdutosPorNome();
void salvarProdutos(const char *nome_arquivo);
void carregarProdutos(const char *nome_arquivo);

#endif
