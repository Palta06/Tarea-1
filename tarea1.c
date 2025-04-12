#include "TDAs/list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 500 //Máximo de caracteres para la descripción del ticket

//Función encargada de limpiar la pantalla
void limpiarPantalla(){
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

//Función que muestra el menú principal
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

//typedef para niveles de prioridad que les asigna un número para facilitar el codigo
typedef enum { BAJO = 1, MEDIO = 2, ALTO = 3 } Prioridad;


//Esctructura con toda la información que lleva el ticket
typedef struct Ticket {
  int id;
  char descripcion[MAX];
  Prioridad prioridad;
  time_t horaRegistro;
} Ticket;

//Función que compara dos tickets para insertar en orden de prioridad y antigüedad
int lower_than(void *a, void *b) {
  Ticket *p1 = (Ticket *)a, *p2 = (Ticket *)b;
  if (p1->prioridad > p2->prioridad) return 1;
  if (p1->prioridad < p2->prioridad) return 0;
  return p1->horaRegistro < p2->horaRegistro; // En caso de misma prioridad, más antiguo va primero
}

//Función que egistra un nuevo ticket dentro de la lista
void registrarTicket(List *colaTickets) {
  limpiarPantalla();
  Ticket *nuevo = malloc(sizeof(Ticket)); //Reserva memoria
  if (nuevo == NULL) {
    printf("Error al asignar memoria.\n");
    return;
  }
  int idIngresado;
  printf("ID del ticket:\n");
  scanf("%d", &idIngresado); //El usuario ingresa el id
  getchar();

  Ticket *actual = list_first(colaTickets);
  while (actual != NULL) {
    if (actual->id == idIngresado) { //Confirmamos que no este el id dentro de la lista para que sea único
      printf("Error: Ya existe un ticket con ese ID.\n");
      free(nuevo);
      return;
    }
    actual = list_next(colaTickets);
  }

  nuevo->id = idIngresado;

  printf("Descripcion del ticket (máximo 500 dígitos):\n");
  fgets(nuevo->descripcion, MAX, stdin);

  int i = 0;
  while (nuevo->descripcion[i] != '\0') {
    if (nuevo->descripcion[i] == '\n') {
      nuevo->descripcion[i] = '\0';
      break;
    }
    i++;
  }

  nuevo->prioridad = BAJO; //Registramos la prioridad como baja de manera automática
  nuevo->horaRegistro = time(NULL); //Registramos la hora en que se registro

  list_sortedInsert(colaTickets, nuevo, lower_than); //Ingresamos el ticket dentro de la lista 
  printf("Ticket registrado con prioridad baja.\n");
}

//Mostramos la informacion del ticket ingresado
void mostrarTicket(Ticket *ticket) {
  limpiarPantalla();
  printf("ID: %d\n", ticket->id); //Mostramos el id del ticket junto con la descripción ingresada
  printf("Descripcion: %s\n", ticket->descripcion);

  switch (ticket->prioridad) { //Mostramos la prioridad asignada
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
    break;
  }

  printf("Hora de registro: %s", ctime(&ticket->horaRegistro)); //Mostramos la hora de registro correspondiente
}

//Mostramos la informacion del ticket ingresado
void mostrarListaTickets(List *colaTickets) {
  limpiarPantalla();
  if (list_size(colaTickets) == 0) { //Confirmamos que hayan tickets registrados
    printf("No hay tickets en espera.\n");
    return;
  }

  Ticket *current = list_first(colaTickets); //Recorremos la lista y llamamos la información de cada ticket
  while (current != NULL) {
    mostrarTicket(current);
    printf("-----------------\n");
    current = list_next(colaTickets);
  }
}

//Función para cambiarle la prioridad a un ticket registrado
void asignarPrioridad(List *colaTickets) {
  limpiarPantalla();
  if (list_size(colaTickets) == 0) { //Confirmamos que hayan tickets registrados
    printf("No hay tickets registrados.\n");
    return;
  }

  int idBuscar;
  printf("Inserte ID del ticket: ");
  scanf("%d", &idBuscar); //Se inserta el ticket que queremos cambiar su prioridad
  while (getchar() != '\n')
    ;

  Ticket *current = list_first(colaTickets);
  while (current && current->id != idBuscar) //Se busca el ticket dentro de la lista
    current = list_next(colaTickets);

  if (current == NULL) {
    printf("Ticket no encontrado.\n"); //No se encontró
    return;
  }

  int nuevaPrioridad;
  printf("\nSeleccione nueva prioridad:\n"); //Ingrese la prioridad que quiere asignarle al ticket
  printf("1. Baja\n2. Media\n3. Alta\nOpcion: ");
  scanf("%d", &nuevaPrioridad);
  while (getchar() != '\n')
    ;

  if (nuevaPrioridad < 1 || nuevaPrioridad > 3) {
    printf("Prioridad inválida.\n");
    return;
  }

  list_popCurrent(colaTickets); //Se elimina para volver a ingresarlo de manera ordenada a como corresponde ahora
  current->prioridad = (Prioridad)nuevaPrioridad;
  current->horaRegistro = time(NULL);
  list_sortedInsert(colaTickets, current, lower_than);

  printf("Prioridad actualizada correctamente.\n");
}

//Función para procesar el ticket de mayor prioridad en la lista
void procesarSiguienteTicket(List *colaTickets) {
  limpiarPantalla();
  if (list_size(colaTickets) == 0) { //Confirmamos que hayan tickets registrados
    printf("No hay tickets para procesar.\n");
    return;
  }

  Ticket *ticket = list_popFront(colaTickets); //Eliminamos el primero, ya que es el que debería procesar primero
  printf("Procesando ticket:\n");
  mostrarTicket(ticket); //Mostramos su datos
  free(ticket); //Liberamos sus datos
}

//Función que busca el ticket con el id ingresado y muestra sus datos en caso de que esté
void buscarTicket(List *colaTickets) {
  limpiarPantalla();
  if (list_size(colaTickets) == 0) { //Confirmamos que hayan tickets registrados
    printf("No hay tickets registrados.\n");
    return;
  }

  int idBuscar;
  printf("Ingrese ID del ticket a buscar: "); //El id que queremos buscar
  scanf("%d", &idBuscar);
  while (getchar() != '\n');

  Ticket *current = list_first(colaTickets);
  while (current && current->id != idBuscar)
    current = list_next(colaTickets);

  if (current == NULL) {
    printf("Ticket no encontrado.\n"); //No se encontró el ticket
    return;
  }

  printf("\nDetalles del ticket:\n");
  mostrarTicket(current); //Mostramos los datos del ticket
}

int main() {
  char opcion;
  List *colaTickets = list_create(); //Creamos la lista vacía

  do {
    mostrarMenu();
    printf("Seleccione una opcion: ");
    scanf(" %c", &opcion);
    while (getchar() != '\n'); // <- AQUI FALTABA EL PUNTO Y COMA

    switch (opcion) {
    case '1':
        registrarTicket(colaTickets);
        break;
    case '2':
        asignarPrioridad(colaTickets);
        break;
    case '3':
        mostrarListaTickets(colaTickets);
        break;
    case '4':
        procesarSiguienteTicket(colaTickets);
        break;
    case '5':
        buscarTicket(colaTickets);
        break;
    case '6':
        puts("Saliendo del sistema...");
        break;
    default:
        puts("Opcion no valida. Intente nuevamente.");
    }

    if (opcion != '6') {
        printf("\nPresione Enter para continuar...");
        while (getchar() != '\n');
    }
    limpiarPantalla();
} while (opcion != '6');

  while (list_size(colaTickets) > 0) { //Liberamos la memoria de todos los tickets ingresadas
    Ticket *ticket = list_popFront(colaTickets);
    free(ticket);
  }
  list_clean(colaTickets); //Limpiamos la lista que teníamos

  return 0;
}
