# Roudin-robin
O Round-Robin é um algoritmo escalonador de processos que consiste em dividir o tempo de uso da CPU . Cada processo recebe uma fatia de tempo, esse tempo é chamado Time-Slice, também conhecido por Quantum. Os processos são todos armazenados em Fila circular.

## Implementação

Declaração das bibliotecas, structs, e funções

```c
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
```

Leitura dos dados
(Quantidade de processos, quantum e os valores de chegada e burst)

```c
scanf("%d %d", &quant_processos, &quantum);
    
for (int i = 0; i < quant_processos; i++) {

        scanf("%d %d", &tempo_chegada, &tempo_necessario);
        adicionando(&head, &tail, tempo_chegada, tempo_necessario);
}
```
Loop
Neste loop acontece toda a logica e calculos.

No 1 if é checado caso o processo tenha tempo de burst menor que o quantum, dessa forma a variavel tempo-necessario é zerada e contador = 1;

No else if seguinte é checado se o processo ja foi zerado, caso não, é subtrido dele o quantum, e total se soma a quantum;

No 2 if se o processo ja foi concluido, caso sim, os dados de tempo de espera, ativo e responta são coletados, o contador zerado e processos incrementa -1;

As três seguintes estruturas de decisão tem a função de avançar na fila ou retormar ao inicio;

Loop finalizado quando acabam os proccessos;

```c
while (processos != 0) {

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
```
Medias e prints

```c
    media_espera = tempo_espera * 1.0 / quant_processos;
    media_resposta = tempo_resposta * 1.0 / quant_processos;
    media_ativo = tempo_ativo *1.0 / quant_processos;
    printf("\nRR %.1f %.1f %.1f", media_ativo, media_resposta, media_espera);
```

Funções auxuliares
```c
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
```
## makefile

Make = Cria o aplicativo binario do codigo.

Make run = Executa o aplicativo.

Make clean = Apaga o aplicativo binario.
