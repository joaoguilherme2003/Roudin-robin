#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct fila {
    int tempo_chegada;
    int tempo_necessario;
    struct fila *next;
};
void adicionando(struct fila **head, struct fila **tail, int a, int b);
int isEmpty(struct fila *head);
int main()
{
    struct fila *head = NULL;
    struct fila *tail = NULL;
    
    int tempo_espera = 0, tempo_resposta = 0, tempo_ativo = 0, tempo_chegada = 0, tempo_necessario = 0, quant_processos, total = 0, contador = 0, quantum = 0;
    float media_espera, media_resposta, media_ativo;

    scanf("%d %d", &quant_processos, &quantum);
    
    for (int i = 0; i < quant_processos; i++) {

        scanf("%d %d", &tempo_chegada, &tempo_necessario);
        adicionando(&head, &tail, tempo_chegada, tempo_necessario);
    }
    
    int processos = quant_processos;

    struct fila *aux = head;
    
    for (total = 0; processos != 0;)  {

        if (aux->tempo_necessario <= quantum && aux->tempo_necessario > 0) {
            total = total + aux->tempo_necessario;
            aux->tempo_necessario = 0;
            contador = 1;
        }
        else if (aux->tempo_necessario > 0) {
            aux->tempo_necessario = aux->tempo_necessario - quantum;
            total = total + quantum;
        }
        if (aux->tempo_necessario == 0 && contador == 1) {
            tempo_espera += total - aux->tempo_chegada - aux->tempo_chegada;
            tempo_resposta += total - aux->tempo_chegada;
            tempo_ativo += total;
            contador = 0;
            processos--;
        }
        if (aux->next == NULL) { 
            aux = head;          
        }
        else if (head->next->tempo_chegada <= total) {
            aux = aux->next;
        }
        else {
            aux = head;
        }
    }
    
    media_espera = tempo_espera * 1.0 / quant_processos;
    media_resposta = tempo_resposta * 1.0 / quant_processos;
    media_ativo = tempo_ativo *1.0 / quant_processos;
    printf("\nRR %.1f %.1f %.1f", media_ativo, media_resposta, media_espera);

    return 0;
}

void adicionando(struct fila **head, struct fila **tail, int a, int b)
{

	struct fila *novo = (struct fila *)malloc(sizeof(struct fila));
	if(novo != NULL){
		novo-> tempo_chegada = a;
		novo -> tempo_necessario = b;
		novo->next = NULL;

		if(isEmpty(*head)){
			*head = novo;
			*tail = novo;
		}
        else {
			(*tail)->next = novo;
			*tail = novo;
		}
	}
}

int isEmpty(struct fila *head) 
{
	return head == NULL;
}
