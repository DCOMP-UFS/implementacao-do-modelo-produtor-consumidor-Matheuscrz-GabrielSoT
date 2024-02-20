/*Alunos:
	GABRIEL DE SOUZA TELES
	MATHEUS LIMA DA CRUZ
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

// Buffer compartilhado entre produtores e consumidores
int buffer[BUFFER_SIZE];
int count = 0;  // Contador de elementos no buffer
int in = 0;     // Índice para inserção no buffer
int out = 0;    // Índice para remoção do buffer

// Mutex e condições para controle de concorrência
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Função do produtor
void* producer(void* arg) {
    // Identificador da thread produtora
    int thread_id = *((int*)arg);

    while (1) {
        // Produzir relógio vetorial
        int clock_value = rand() % 100;

        // Bloqueio: Adquirir o mutex antes de acessar a região crítica
        pthread_mutex_lock(&mutex);

        // Bloqueio: Esperar até que haja espaço no buffer
        while (count == BUFFER_SIZE) {
            printf("Produtor %d bloqueado - Buffer cheio\n", thread_id);
            pthread_cond_wait(&not_full, &mutex);
        }

        // Inserir no buffer
        buffer[in] = clock_value;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produtor %d produziu 1 relógio vetorial. Total no buffer: %d\n", thread_id, count);

        // Desbloqueio: Notificar consumidores que o buffer não está mais vazio
        pthread_cond_signal(&not_empty);
        // Desbloqueio: Liberar o mutex após acessar a região crítica
        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
}

// Função do consumidor
void* consumer(void* arg) {
    // Identificador da thread consumidora
    int thread_id = *((int*)arg);

    while (1) {
        // Bloqueio: Adquirir o mutex antes de acessar a região crítica
        pthread_mutex_lock(&mutex);

        // Bloqueio: Esperar até que haja itens no buffer
        while (count == 0) {
            printf("Consumidor %d bloqueado - Buffer vazio\n", thread_id);
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remover do buffer
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumidor %d consumiu 1 relógio vetorial. Total no buffer: %d\n", thread_id, count);

        // Desbloqueio: Notificar produtores que o buffer não está mais cheio
        pthread_cond_signal(&not_full);
        // Desbloqueio: Liberar o mutex após acessar a região crítica
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Criar threads produtoras
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        pthread_create(&producers[i], NULL, producer, (void*)thread_id);
    }

    // Criar threads consumidoras
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int* thread_id = malloc(sizeof(int));
        *thread_id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, (void*)thread_id);
    }

    // Aguardar o término das threads produtoras
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Aguardar o término das threads consumidoras
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
