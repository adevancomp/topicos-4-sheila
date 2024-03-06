#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"

int menu(void);

int main(int argc, char const *argv[])
{
    recupera_os_dados();
    int cliente_ou_produto = -1;
    int escolha = -1;
    for(;;){
        printf("0 - Em cliente\n1- Em produto\nescolha: ");
        scanf("%d",&cliente_ou_produto);
        escolha = menu();
        if(cliente_ou_produto==0){
            // Em cliente
            switch (escolha)
            {
            case 1:
                cliente novo_cliente;
                printf("cod: ");
                scanf("%d",&(novo_cliente.cod));
                getchar();
                printf("nome: ");
                fgets(novo_cliente.nome,100,stdin);
                printf("idade: ");
                scanf("%d",&(novo_cliente.idade));
                getchar();
                adiciona_cliente(novo_cliente);
                break;

            case 2:
                int cod;
                cliente* cliente_buscado;
                printf("Insira o cod: ");
                scanf("%d",&cod);
                cliente_buscado = busca_cliente_por_codigo(cod);
                if(cliente_buscado==NULL){
                    printf("Este cliente não existe!!\n");
                } else {
                    mostrar_um_cliente(*cliente_buscado);
                }
                break;
            case 3:
                for(int i=0;i<20;i++){
                    if(clientes[i].cod!=-1){
                        mostrar_um_cliente(clientes[i]);
                    }
                }
                break;
            case 4:
                printf("Insira o cod: ");
                scanf("%d",&cod);
                excluir_um_cliente_por_codigo(cod);
            default:
                break;
            }
        } else if(cliente_ou_produto==1){

            // Em Produtos
            switch (escolha)
            {
            case 1:
                produto novo_produto;
                printf("cod: ");
                scanf("%d",&(novo_produto.cod));
                getchar();
                printf("nome: ");
                fgets(novo_produto.nome,100,stdin);
                printf("valor: ");
                scanf("%lf",&(novo_produto.valor));
                getchar();
                adiciona_produto(novo_produto);
                break;

            case 2:
                int cod;
                produto* produto_buscado;
                printf("Insira o cod: ");
                scanf("%d",&cod);
                produto_buscado = busca_produto_por_codigo(cod);
                if(produto_buscado==NULL){
                    printf("Este Produto nao existe!!\n");
                } else {
                    mostrar_um_produto(*produto_buscado);
                }
                break;
            case 3:
                for(int i=0;i<20;i++){
                    if(produtos[i].cod!=-1){
                        mostrar_um_produto(produtos[i]);
                    }
                }
                break;
            case 4:
                printf("Insira o cod: ");
                scanf("%d",&cod);
                excluir_um_produto_por_codigo(cod);
            default:
                break;
            }

        } else {
            break;
        }
    }
    salvar_clientes();
    salvar_produtos();
    return 0;
}

int menu(void){
    int escolha = -1;
    printf("\n==== Sistema de Gerenciamento ====\n");
    printf("1. Cadastrar\n");
    printf("2. Busca por um\n");
    printf("3. Listar todos\n");
    printf("4. Excluir um\n");
    printf("Demais Numeros- Sair\n");
    printf("Escolha uma opcao: ");
    
    do{
        scanf("%d", &escolha);
    } while(escolha<1 && escolha>4);
    return escolha;
}