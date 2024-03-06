#include "mercado.h"
#include <stdio.h>

cliente clientes[20];
produto produtos[20];

FILE* fp_cliente;
FILE* fp_produto;

/*A função inicializa a lista de clientes com valores inválidos*/
void inicializa_lista_clientes(){
    for(int i=0;i<20;i++){
        clientes[i].cod = -1;
        clientes[i].nome[0] = '\0',
        clientes[i].idade = -1;
    }
}

/*A função inicializa a lista de produtos com valores inválidos*/
void inicializa_lista_produtos(){
    for(int i=0;i<20;i++){
        produtos[i].cod = -1;
        produtos[i].nome[0] = '\0';
        produtos[i].valor = 0.0;
    }
}

/*A função adiciona cliente pega um registro do tipo cliente e adiciona
na primeira posição que está livre (com valor inválido de cod)
senão encontrar, a lista está cheia e avisa como o printf*/
void adiciona_cliente(cliente novo_cliente){
    int cont = 0;
    while(cont<20){
        if(clientes[cont].cod==-1){
            clientes[cont] = novo_cliente;
            return;
        }
        cont++;
    }
    printf("Lista de clientes esta cheia!!!!!");
}

/*A função adiciona produto pega um registro do tipo produto e adiciona
na primeira posição que está livre (com valor inválido de cod)
senão encontrar, a lista está cheia e avisa como o printf*/
void adiciona_produto(produto novo_produto){
    for(int i=0;i<20;i++){
        if(produtos[i].cod == -1){
            produtos[i] = novo_produto;
            return;
        }
    }
    printf("Lista de produtos esta cheia!!!!!");
}

/*A função encontra o cliente pelo seu atributo código
Importante que na hora de cadastrar sejam valores únicos
Se ele não encontrar, retornar nulo. Se ele encontrar, 
retorna um ponteiro pra posição do elemento na lista*/

cliente* busca_cliente_por_codigo(int cod){
    int cont =0;
    while(cont<20){
        if(clientes[cont].cod == cod){
            return clientes+cont;
        }
        cont++;
    }
    return  NULL;
}

/*A função encontra o produto pelo seu atributo código
Importante que na hora de cadastrar sejam valores únicos
Se ele não encontrar, retornar nulo. Se ele encontrar, 
retorna um ponteiro pra posição do elemento na lista*/
produto* busca_produto_por_codigo(int cod){
    for(int i=0;i<20;i++){
        if(produtos[i].cod == cod){
            return produtos+i;
        }
    }
    return NULL;
}

/*Printf Estilizado pra produto*/
void mostrar_um_produto(produto meu_produto){
    printf("\n<<|| ");
    printf("codigo: %d nome:%s valor:%6.3f",meu_produto.cod, meu_produto.nome,meu_produto.valor);
    printf(" ||>>\n");
}

/*Printf Estilizado pra cliente*/
void mostrar_um_cliente(cliente meu_cliente){
    printf("\n## ");
    printf("codigo: %d nome:%s idade:%d",meu_cliente.cod, meu_cliente.nome,meu_cliente.idade);
    printf(" ##\n");
}

/*a função excluir_um_produto_por_codigo procura o elemento com o código
passado como parâmetro. Se ele encontrar, deixo o campo inválido. Indicando
que está livre*/
void excluir_um_produto_por_codigo(int cod){
    produto* produto_a_excluir = busca_produto_por_codigo(cod);
    if(produto_a_excluir!=NULL){
        produto_a_excluir->cod = -1;
        produto_a_excluir->nome[0] = '\0';
        produto_a_excluir->valor=0.0;
    }
}

/*a função excluir_um_cliente_por_codigo procura o elemento com o código
passado como parâmetro. Se ele encontrar, deixo o campo inválido. Indicando
que está livre*/
void excluir_um_cliente_por_codigo(int cod){
    cliente* cliente_a_excluir = busca_cliente_por_codigo(cod);
    if(cliente_a_excluir!=NULL){
        cliente_a_excluir->cod = -1;
        cliente_a_excluir->nome[0] = '\0';
        cliente_a_excluir->idade = -1;
    }
}

/*A função salvar_clientes pega o estado atual da lista de clientes e salva no arquivo*/
void salvar_clientes(void){
    fp_cliente = fopen(FP_CLIENTE,"wb");
    for(int i=0;i<20;i++){
        if(clientes[i].cod!=-1){
            if(fwrite(clientes+i,sizeof(cliente),1,fp_cliente)!=1)
                printf("Erro na escrita do arquivo!\n");
        }
    }
}

/*A função salvar_clientes pega o estado atual da lista de produtos e salva no arquivo*/
void salvar_produtos(void){
    fp_produto = fopen(FP_PRODUTO,"wb");
    for(int i=0;i<20;i++){
        if(produtos[i].cod!=-1){
            if(fwrite(produtos+i,sizeof(produto),1,fp_produto)!=1)
                printf("Erro na escrita do arquivo!\n");
        }
    }
}

/*A função ler clientes faz a leitura do arquivo e armazena na lista de clientes*/
void ler_clientes(void){
    fp_cliente = fopen(FP_CLIENTE,"rb");
    for(int i=0;i<20;i++){
        if(fread(clientes+i,sizeof(cliente),1,fp_cliente)!=1){
            if(feof(fp_cliente)) break;
        }
    }
}

/*A função ler produtos faz a leitura do arquivo e armazena na lista de produtos*/
void ler_produtos(void){
    fp_produto = fopen(FP_PRODUTO,"rb");
    for(int i=0;i<20;i++){
        if(fread(produtos+i,sizeof(produto),1,fp_produto)!=1){
            if(feof(fp_produto)) break;
        }
    }
}

/*Esta função primeira tenta abrir os arquivos,
 se ela conseguir carrega nas listas o que tinha em cada um
 Senão, deixa as listas com valores inválidos mesmo*/
void recupera_os_dados(void){
    fp_cliente = fopen(FP_CLIENTE,"rb");
    fp_produto = fopen(FP_PRODUTO,"rb");
    if(fp_cliente!=NULL && fp_produto!=NULL){
        inicializa_lista_clientes();
        inicializa_lista_produtos();
        ler_clientes();
        ler_produtos();
    } else {
        inicializa_lista_clientes();
        inicializa_lista_produtos();
    }
}
