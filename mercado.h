#include <stdio.h>

#ifndef MERCADO_H
#define MERCADO_H

#define FP_CLIENTE "cliente"
#define FP_PRODUTO "produto"

/*Definindo meu registro de produto com os atributos: cod, nome e valor*/
typedef struct {
    int cod;
    char nome[100];
    double valor;
} produto;


/*Definindo meu registro de cliente com os atributos: cod, nome e idade*/
typedef struct {
    int cod;
    char nome[500];
    int idade;
} cliente;

/* Definindo minhas listas usadas tanto para leitura quanto pra armazenamento arquivo texto*/

extern cliente clientes[20];
extern produto produtos[20];
extern FILE* fp_cliente;
extern FILE* fp_produto;

/* Funções de manipulação e armazenamento dos meus registros*/

void inicializa_lista_clientes();
void inicializa_lista_produtos();
void adiciona_cliente(cliente novo_cliente);
void adiciona_produto(produto novo_produto);
cliente* busca_cliente_por_codigo(int cod);
produto* busca_produto_por_codigo(int cod);
void mostrar_um_produto(produto meu_produto);
void mostrar_um_cliente(cliente meu_cliente);
void excluir_um_produto_por_codigo(int cod);
void excluir_um_cliente_por_codigo(int cod);
void salvar_clientes(void);
void salvar_produtos(void);
void ler_clientes(void);
void ler_produtos(void);
void recupera_os_dados(void);

#endif