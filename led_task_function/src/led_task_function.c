#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definições dos pinos GPIO para os LEDs do semáforo
#define SEMAFORO_VERMELHO_PIN   13  // Pino para o LED vermelho
#define SEMAFORO_VERDE_PIN      11  // Pino para o LED verde
#define SEMAFORO_BLUE_PIN    12  // Pino para o LED azul

// Função para inicializar os pinos GPIO do semáforo
void inicializar_semaforo_gpio()
{
    // Configuração do pino do LED vermelho
    gpio_init(SEMAFORO_VERMELHO_PIN);
    gpio_set_dir(SEMAFORO_VERMELHO_PIN, GPIO_OUT);
    
    // Configuração do pino do LED verde
    gpio_init(SEMAFORO_VERDE_PIN);
    gpio_set_dir(SEMAFORO_VERDE_PIN, GPIO_OUT);
    
    // Configuração do pino do LED azul
    gpio_init(SEMAFORO_BLUE_PIN);
    gpio_set_dir(SEMAFORO_BLUE_PIN, GPIO_OUT);
    
    // Desliga todos os LEDs inicialmente
    gpio_put(SEMAFORO_VERMELHO_PIN, 0);
    gpio_put(SEMAFORO_VERDE_PIN, 0);
    gpio_put(SEMAFORO_BLUE_PIN, 0);
}

// Tarefa principal do semáforo
void tarefa_semaforo(void *parametros)
{
    while (true) {
        // Fase Vermelha - Pare (5 segundos)
        gpio_put(SEMAFORO_VERMELHO_PIN, 1);    // Acende vermelho
        gpio_put(SEMAFORO_VERDE_PIN, 0);        // Apaga verde
        gpio_put(SEMAFORO_BLUE_PIN, 0);      // Apaga azul
        printf("[SEMAFORO] Fase VERMELHA - PARE\n");
        printf("Tempo restante: ");
        for (int contador = 5; contador > 0; contador--) {
            printf("%d ", contador);
            vTaskDelay(pdMS_TO_TICKS(1000));    // Espera 1 segundo
        }
        printf("\n");

        // Fase Verde - Siga (5 segundos)
        gpio_put(SEMAFORO_VERMELHO_PIN, 0);     // Apaga vermelho
        gpio_put(SEMAFORO_VERDE_PIN, 1);        // Acende verde
        gpio_put(SEMAFORO_BLUE_PIN, 0);      // Apaga azul
        printf("[SEMAFORO] Fase VERDE - SIGA\n");
        printf("Tempo restante: ");
        for (int contador = 5; contador > 0; contador--) {
            printf("%d ", contador);
            vTaskDelay(pdMS_TO_TICKS(1000));    // Espera 1 segundo
        }
        printf("\n");

        // Fase Amarela - Atenção (3 segundos)
        gpio_put(SEMAFORO_VERMELHO_PIN, 1);     // Apaga vermelho
        gpio_put(SEMAFORO_VERDE_PIN, 1);        // Apaga verde
        gpio_put(SEMAFORO_BLUE_PIN, 0);      // Acende azul
        printf("[SEMAFORO] Fase AMARELA - ATENCAO\n");
        printf("Tempo restante: ");
        for (int contador = 3; contador > 0; contador--) {
            printf("%d ", contador);
            vTaskDelay(pdMS_TO_TICKS(1000));    // Espera 1 segundo
        }
        printf("\n");
    }
}

int main()
{
    // Inicializa a comunicação serial
    stdio_init_all();
    sleep_ms(2000);  // Espera para estabilização da serial
    printf("Sistema de Controle de Semaforo Iniciado\n");
    printf("Versao 1.0 - Raspberry Pi Pico\n\n");

    // Inicializa os pinos GPIO do semáforo
    inicializar_semaforo_gpio();

    // Cria a tarefa do semáforo com FreeRTOS
    xTaskCreate(
        tarefa_semaforo,          // Função da tarefa
        "Controle Semaforo",      // Nome da tarefa
        256,                      // Tamanho da pilha
        NULL,                     // Parâmetros
        2,                        // Prioridade
        NULL                      // Handle da tarefa
    );

    // Inicia o escalonador do FreeRTOS
    vTaskStartScheduler();

    // Loop infinito - não deve ser alcançado
    while (1) {
        // Se o escalonador falhar, ficaremos presos aqui
    }
}