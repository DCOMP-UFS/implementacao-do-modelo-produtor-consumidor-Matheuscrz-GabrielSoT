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
#define NUM_PRODUTORES 3
#define NUM_CONSUMIDORES 3

// Buffer compartilhado entre produtores e consumidores
int buffer[BUFFER_SIZE];
int count = 0;  // Contador de elementos no buffer
int in = 0;     // �ndice para inser��o no buffer
int out = 0;    // �ndice para remo��o do buffer

// Mutex e condi��es para controle de concorr�ncia
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Fun��o do produtor
void* produtor(void* arg) {
    // Identificador da thread produtora
    int id_thread = *((int*)arg);

    while (1) {
        // Produzir rel�gio vetorial
        int valor_relogio = rand() % 100;

        // Bloqueio: Adquirir o mutex antes de acessar a regi�o cr�tica
        pthread_mutex_lock(&mutex);

        // Bloqueio: Esperar at� que haja espa�o no buffer
        while (count == BUFFER_SIZE) {
            printf("Produtor %d bloqueado - Buffer cheio\n", id_thread);
            pthread_cond_wait(&not_full, &mutex);
        }

        // Inserir no buffer
        buffer[in] = valor_relogio;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produtor %d produziu 1 rel�gio vetorial. Total no buffer: %d\n", id_thread, count);

        // Desbloqueio: Notificar consumidores que o buffer n�o est� mais vazio
        pthread_cond_signal(&not_empty);
        // Desbloqueio: Liberar o mutex ap�s acessar a regi�o cr�tica
        pthread_mutex_unlock(&mutex);

        sleep(2);  // Produtor dorme mais tempo
    }
}

// Fun��o do consumidor
void* consumidor(void* arg) {
    // Identificador da thread consumidora
    int id_thread = *((int*)arg);

    while (1) {
        // Bloqueio: Adquirir o mutex antes de acessar a regi�o cr�tica
        pthread_mutex_lock(&mutex);

        // Bloqueio: Esperar at� que haja itens no buffer
        while (count == 0) {
            printf("Consumidor %d bloqueado - Buffer vazio\n", id_thread);
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remover do buffer
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumidor %d consumiu 1 rel�gio vetorial. Total no buffer: %d\n", id_thread, count);

        // Desbloqueio: Notificar produtores que o buffer n�o est� mais cheio
        pthread_cond_signal(&not_full);
        // Desbloqueio: Liberar o mutex ap�s acessar a regi�o cr�tica
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Consumidor dorme menos tempo
    }
}

int main() {
    pthread_t produtores[NUM_PRODUTORES];
    pthread_t consumidores[NUM_CONSUMIDORES];

    // Criar threads produtoras
    for (int i = 0; i < NUM_PRODUTORES; i++) {
        int* id_thread = malloc(sizeof(int));
        *id_thread = i + 1;
        pthread_create(&produtores[i], NULL, produtor, (void*)id_thread);
    }

    // Criar threads consumidoras
    for (int i = 0; i < NUM_CONSUMIDORES; i++) {
        int* id_thread = malloc(sizeof(int));
        *id_thread = i + 1;
        pthread_create(&consumidores[i], NULL, consumidor, (void*)id_thread);
    }

    // Aguardar o t�rmino das threads produtoras
    for (int i = 0; i < NUM_PRODUTORES; i++) {
        pthread_join(produtores[i], NULL);
    }

    // Aguardar o t�rmino das threads consumidoras
    for (int i = 0; i < NUM_CONSUMIDORES; i++) {
        pthread_join(consumidores[i], NULL);
    }

    return 0;
}
