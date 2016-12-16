#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
struct Node{
	int num;
	struct Node *prox;
}; 
typedef struct Node node;
unsigned int Head, Tail;
float inicio, final, tmili;

void inicia(node *fila);
int menu(void);
void opcao(node *fila, int op);
node *criaNo();
node *dequeue();
int enqueue(node *fila);
void insereFim(node *fila);
void exibe(node *fila);
void libera(node *fila);


int main(void)
{
	//códigos para medir o tempo de execução
	
    //cria lista
	node *fila = (node *) malloc(sizeof(node));
	if(!fila){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	//inicia a lista
	inicia(fila);
	int opt;
	
	do{
		opt=menu();
		opcao(fila,opt);
	}while(opt);

	free(fila);
	return 0;
}
int LL(int *ptr){
	   return *ptr;	
}

int SC(int *ptr, int value){
	//caso o ponteiro ptr não tenha sido atualizado na operação LL
	//VERIFICAR SE O PROCEDIMENTO NO IF ABAIXO SEGUE A LÓGICA DA IMPLEMENTAÇÃO
	
	if(*ptr != value){
		*ptr = value;
		return 1;//operação realizada com sucesso
	}else{
		return 0;//operação não realizada
	}
}

void inicia(node *fila)
{
	fila->prox = NULL;
}

int menu(void)
{
	int opt;
	
	printf("Escolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Exibir lista\n");
	printf("2. Remover node no inicio\n");
	printf("3. Adicionar node no final\n");
	printf("4. Zerar lista\n");
	printf("Opcao: "); scanf("%d", &opt);
	
	return opt;
}

void opcao(node *fila, int op)
{
	int valor;
	double i = 0;
	node *fila_aux[5000];
	switch(op){
		case 0:
			libera(fila);
			break;
			
		case 1:
			inicio = GetTickCount();
			exibe(fila);
			
			final = GetTickCount();
    		tmili = ((final - inicio)/1000); 
    		printf("tempo decorrido em segundos: %.5f\n", tmili); 
			
			break;
		
		case 2:
			dequeue();
			break;
		
		case 3:
			
			//node *testa = (node *) malloc(sizeof(node));
			//INSTRUÇÃO REFERENTE A INSERÇÃO DO VALOR FEITA PELO USUÁRIO
			//printf("Novo Elemento: ");
			//scanf("%d",&fila->num);
			inicio = GetTickCount();
			
			for(i=0;i<=100000;i++){
				fila->num = i+1;
				enqueue(fila);
			}
			
			final = GetTickCount();
    		tmili = ((final - inicio)/1000); 
    		printf("tempo decorrido em segundos: %.4f\n", tmili); 
			//printf("%d\n",i);
			//AQUI IRÁ O O O FINAL DA VAR TEMPO
			//printf("acabou");
			//enqueue(fila);
			break;		
			
		case 4:
			inicia(fila);
			break;
		
		default:
			printf("Comando invalido\n\n");
	}
}

int vazia(node *fila)
{
	if(fila->prox == NULL)
		return 1;
	else
		return 0;
}

//no artigo o cara cria uma array de um nó igual a linha de baixo
node *array[100000];

void exibe(node *fila)
{
	printf("\n\nItens Gravados:\n");
	int i = 0;
	//printf("\nValor do I: %d\n",i);
	//não aparece os valores da remoção pq o primeiro esta nulo
	//reformular a lógica
    while(array[i] != NULL){
        
        printf("%d ",array[i]); 
        i++;                   
    }
    i = 0;
    	
		
	printf("\n\n");
}
	
//método para inserção
//trocar o tipo de parametro recebido
//int enqueue(node *fila){

node *dequeue(void) {
	unsigned int h, head;
	node *slot = (node*)malloc(sizeof(node));
	
    while (1) {
		h = Head;
        if (h == Tail){  
			return NULL;
        }
      
		head = h % 100000;
        slot->num = LL(&array[head]);
		
        if (h == Head){
            if (slot->num == NULL) {
                if (LL(&Head) == h){
                    SC(&Head,h+1);
                }
			}else if (SC(&array[head],NULL)) {
                if (LL(&Head) == h){		
                    SC(&Head,h+1);	
                }
				return slot;
			}
        }
    }
}
	
int enqueue(node *fila){
     unsigned int t,tail;
     //node *slot;
     node *slot = (node*)malloc(sizeof(node));
     
     while(1){
        t = Tail;
        //if abaixo verifica se a fila esta cheia
        if(t == (Head + 100000)){ // a propriedade q_length se refere ao tamanho da fila
			 return 0;     
         	 //trocar por 0
        }     
        tail = t % 100000; // a propriedade q_length se refere ao tamanho da fila
      	slot->num = LL(&array[tail]);  //a propriedade q se refere a propria fila     
        slot->prox = NULL;
		
		if(t == Tail){
        	//slot->num != NULL
			 if(slot->num != NULL){
                  	  if(LL(&Tail) == t){
                  			SC(&Tail,t+1);
                      }         
             }else if(SC(&array[tail],fila->num)){
                   if(LL(&Tail)== t){
                        SC(&Tail, t+1);               
                   } 
                   return 1;    
				   //trocar por 1 
             }
        }
     }
}

void libera(node *fila)
{
	if(!vazia(fila)){
		node *proxNode,
			  *atual;
		
		atual = fila->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}
