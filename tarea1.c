#include "TDAs/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void mostrarMenu() {
    puts("========================================");
    puts("     Sistema de Gestion Hospitalaria");
    puts("========================================");
  
    puts("1) Registrar nuevo paciente");
    puts("2) Asignar prioridad a paciente");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente paciente");
    puts("5) Buscar detalles de Paciente");
    puts("6) Salir");
  }

typedef enum { 
    BAJO = 1,
    MEDIO = 2,
    ALTO = 3 
    } Prioridad;

typedef struct Ticket {
    char id;
    char descripcion;
    Prioridad prioridad;
    time_t horaRegistro;
} Ticket;

int lower_than(void *a, void *b) {
    Ticket *p1 = a, *p2 = b;
    if (p1->prioridad > p2->prioridad) return 1;
    if (p1->prioridad < p2->prioridad) return 0;
    return p1->horaRegistro < p2->horaRegistro;
  }

void registrarPaciente(List *colaPacientes){
    Ticket *nuevo = malloc(sizeof(Ticket));
    printf("ID del paciente:\n");
    scanf("%c", &nuevo->id);
    getchar();
    printf("Descripcion del paciente:\n");
    scanf("%c", &nuevo->descripcion);
    getchar();
    nuevo->prioridad = BAJO;
    nuevo->horaRegistro = time(NULL);

    list_sortedInsert(colaPacientes, nuevo, lower_than);
    printf("Paciente registrado con prioridad baja.\n");
}

void mostrar_lista_pacientes(List *colaPacientes) {
    if (list_size(colaPacientes) == 0) {
      printf("No hay pacientes en espera.\n");
      return;
    }
    
    Ticket *current = list_first(colaPacientes);
    while (current != NULL) {
      printf("ID: %c\n", current->id);
      printf("Descripcion: %c\n", current->descripcion);
      printf("Prioridad: %c\n", current->prioridad);
      current = list_next(colaPacientes);
    }
}

int main() {
    int opcion;
    List *colaPacientes = list_create();

    do{
        mostrarMenu();
        scanf("%d", &opcion);
        getchar();
        switch (opcion) {
        case 1:
        registrarPaciente(colaPacientes);
        break;
        case 2:
        // Lógica para asignar prioridad
        break;
        case 3:
        mostrar_lista_pacientes(colaPacientes);
        break;
        case 4:
        // Lógica para atender al siguiente paciente
        break;
        case 5:
        // Lógica para mostrar pacientes por prioridad
        break;
        case 6:
        puts("Saliendo del sistema de gestion hospitalaria...");
        break;
        default:
        puts("Opcion no valida. Por favor, intente de nuevo.");
        }

    } while (opcion != '6');
    if (opcion != 6){
        printf("Presione cualquier tecla para continuar...\n");
        getchar();
    }

  list_clean(colaPacientes);

  return 0;
}