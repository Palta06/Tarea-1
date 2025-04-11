#include "TDAs/list.h"
#include "TDAs/list.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX 200

void mostrarMenu() {
    puts("========================================");
    puts("     Sistema de Gestion de tickets");
    puts("========================================\n");
  
    puts("1. Registrar nuevo ticket");
    puts("2. Asignar prioridad a ticket");
    puts("3. Mostrar lista de espera");
    puts("4. Procesar siguiente ticket");
    puts("5. Buscar detalles de ticket");
    puts("6. Salir");
  }

typedef enum { 
    BAJO = 1,
    MEDIO = 2,
    ALTO = 3 
} Prioridad;

typedef struct Ticket {
    int id;
    char descripcion[MAX];
    Prioridad prioridad;
    time_t horaRegistro;
} Ticket;

int lower_than(void *a, void *b) {
    Ticket *p1 = a, *p2 = b;
    if (p1->prioridad > p2->prioridad) return 1;
    if (p1->prioridad < p2->prioridad) return 0;
    return p1->horaRegistro < p2->horaRegistro;
  }

void registrarTicket(List *colaTickets){
    Ticket *nuevo = malloc(sizeof(Ticket));
    printf("ID del ticket:\n");
    scanf("%d", &nuevo->id);
    getchar();
    printf("Descripcion del ticket:\n");
    scanf("%c", &nuevo->descripcion);
    getchar();
    nuevo->prioridad = BAJO;
    nuevo->horaRegistro = time(NULL);

    list_sortedInsert(colaTickets, nuevo, lower_than);
    printf("Ticket registrado con prioridad baja.\n");
}

void mostrarListaTickets(List *colaTickets) {
    if (list_size(colaTickets) == 0) {
      printf("No hay tickets en espera.\n");
      return;
    }
    
    Ticket *current = list_first(colaTickets);
    while (current != NULL) {
      printf("ID: %d\n", current->id);
      printf("Descripcion: %c\n", current->descripcion);
      
      switch (current->prioridad) {
        case BAJO:
            printf("Prioridad: Baja\n");
            break;
        case MEDIO:
            printf("Prioridad: Media\n");
            break;
        case ALTO:
            printf("Prioridad: Alta\n");
            break;
        default:
            printf("Prioridad desconocida\n");
            current->prioridad = BAJO;
            break;
    }
      current = list_next(colaTickets);
    }
}

void asignarPrioridad(List *colaTickets) {
    if (list_size(colaTickets) == 0) {
        printf("No hay tickets registrados.\n");
        return;
    }

    int idBuscar;
    printf("Inserte ID del ticket\n");
    scanf("%d", &idBuscar);
    while (getchar() != '\n');

    Ticket *current = list_first(colaTickets);
    while (current && current->id != idBuscar)
        current = list_next(colaTickets);

    if (current == NULL) {
        printf("Ticket no encontrado.\n");
        return;
    }

    int nuevaPrioridad;
    printf("Inserte nueva prioridad\n");
    printf("Inserte 1 para asignar prioridad baja\n");
    printf("Inserte 2 para asignar prioridad media\n");
    printf("Inserte 3 para asignar prioridad alta\n");
    scanf("%d", &nuevaPrioridad);
    while (getchar() != '\n');

    if (nuevaPrioridad < 1 || nuevaPrioridad > 3) {
        printf("Prioridad inválida.\n");
        return;
    }

    list_popCurrent(colaTickets);
    current->prioridad = nuevaPrioridad;
    current->horaRegistro = time(NULL);
    list_sortedInsert(colaTickets, current, lower_than);

    printf("Prioridad actualizada.\n");
}

int main() {
    int opcion;
    List *colaTickets = list_create();

    do{
        mostrarMenu();
        scanf("%c", &opcion);
        getchar();
        switch (opcion) {
        case 1:
        registrarTicket(colaTickets);
        break;
        case 2:
        asignarPrioridad(colaTickets);
        break;
        case 3:
        mostrarListaTickets(colaTickets);
        break;
        case 4:
        // Lógica para atender al siguiente paciente
        break;
        case 5:
        // Lógica para mostrar pacientes por prioridad
        break;
        case 6:
        puts("Saliendo del sistema de gestion de tickets...");
        break;
        default:
        puts("Opcion no valida. Por favor, intente de nuevo.");
        }

    } while (opcion != 6);
    printf("Presione cualquier tecla para continuar...\n");

  list_clean(colaTickets);

  return 0;
}
