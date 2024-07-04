#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void cargarClientes(char clientes[][2][40]) {
    FILE *file = fopen("clientes.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        fscanf(file, "%s %s", clientes[i][0], clientes[i][1]);
    }
    fclose(file);
}

void guardarClientes(char clientes[][2][40]) {
    FILE *file = fopen("clientes.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%s %s\n", clientes[i][0], clientes[i][1]);
    }
    fclose(file);
}

void cargarHabitaciones(char habitaciones[][3][40], double precios[]) {
    FILE *file = fopen("habitaciones.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de habitaciones.\n");
        return;
    }
    for (int i = 0; i < 9; i++) {
        fscanf(file, "%s %s %s %lf", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], &precios[i]);
    }
    fclose(file);
}

void cargarReservas(int reservas[][4]) {
    FILE *file = fopen("reservas.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de reservas.\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        fscanf(file, "%d %d %d %d", &reservas[i][0], &reservas[i][1], &reservas[i][2], &reservas[i][3]);
    }
    fclose(file);
}

void guardarReservas(int reservas[][4]) {
    FILE *file = fopen("reservas.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de reservas.\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        fprintf(file, "%d %d %d %d\n", reservas[i][0], reservas[i][1], reservas[i][2], reservas[i][3]);
    }
    fclose(file);
}

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tipo[40];
    printf("Ingrese el tamaño de habitación que desea buscar: ");
    scanf("%s", tipo);
    printf("#\t\tTamaño\t\tHotel\t\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Elija el número de habitación que desea reservar: ");
    scanf("%d", numHabitacion);
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char hotel[40];
    printf("Ingrese el hotel que desea buscar: ");
    getchar();  // Limpiar el buffer de entrada
    fgets(hotel, 40, stdin);

    hotel[strcspn(hotel, "\n")] = '\0'; // Eliminar el salto de línea si existe

    printf("#\t\tTamaño\t\tHotel\t\t\tPrecio\n");
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], hotel) == 0) {
            printf("%s\t\t%s\t\t%s\t\t%.2lf\n", habitaciones[i][0], habitaciones[i][1], habitaciones[i][2], precios[i]);
        }
    }
    printf("Elija el número de habitación que desea reservar: ");
    scanf("%d", numHabitacion);
}

void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    char nombre[40];
    int encontrado = 0, diasReserva;

    printf("Ingrese su nombre:\n>> ");
    scanf("%s", nombre);
    printf("Ingrese su número de cédula:\n>> ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], "") == 0) {
            strcpy(clientes[i][0], nombre);
            strcpy(clientes[i][1], cedula);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No hay espacio para más clientes.\n");
        return;
    }

    printf("Ingrese el número de días de la reserva:\n>> ");
    scanf("%d", &diasReserva);

    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            for (int j = 0; j < 5; j++) {
                if (strcmp(clientes[j][1], cedula) == 0) {
                    reservas[i][0] = j;
                    break;
                }
            }
            reservas[i][1] = numHabitacion; // número de habitación
            reservas[i][2] = diasReserva;   // número de días de reserva
            reservas[i][3] = 1;             // estado de la reserva (1: reservado, 2: pagado)
            guardarClientes(clientes);
            guardarReservas(reservas);
            printf("Reserva realizada con éxito.\n");
            return;
        }
    }

    printf("No hay espacio para más reservas.\n");
}

int buscarReservaPorCedula(int numReservas[], char clientes[][2][40], int reservas[][4]) {
    char cedula[40];
    int count = 0;
    printf("Ingrese su número de cédula:\n>> ");
    scanf("%s", cedula);

    for (int i = 0; i < 10; i++) {
        if ((reservas[i][3] == 1 || reservas[i][3] == 2) && strcmp(clientes[reservas[i][0]][1], cedula) == 0) {
            numReservas[count++] = i;
        }
    }

    if (count == 0) {
        printf("Reserva no encontrada.\n");
    }

    return count;
}

void imprimirReserva(int numReservas[], int count, char clientes[][2][40], int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (count == 0) {
        printf("No se pueden imprimir las reservas: número de reservas inválido.\n");
        return;
    }

    for (int k = 0; k < count; k++) {
        int numReserva = numReservas[k];
        int indexCliente = reservas[numReserva][0];
        int indexHabitacion = reservas[numReserva][1];
        int numDias = reservas[numReserva][2];
        int estadoReserva = reservas[numReserva][3];
        indexHabitacion--;
        const char *estado;
        if (estadoReserva == 1) {
            estado = "Reservado";
        } else {
            estado = "Pagado";
        }

        printf("=== Detalles de la Reserva ===\n");
        printf("Cliente: %s\n", clientes[indexCliente][0]); // nombre del cliente
        printf("Cédula: %s\n", clientes[indexCliente][1]);  // cédula del cliente
        printf("Habitación: %s\n", habitaciones[indexHabitacion][0]); // número de habitación
        printf("Tipo: %s\n", habitaciones[indexHabitacion][1]); // tipo de habitación
        printf("Hotel: %s\n", habitaciones[indexHabitacion][2]); // hotel
        printf("Número de días: %d\n", numDias); // número de días de la reserva
        printf("Estado: %s\n", estado); // estado de la reserva
    }
}

void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No se puede pagar la reserva: número de reserva inválido.\n");
        return;
    }

    int indexHabitacion = reservas[numReserva][1];
    int numDias = reservas[numReserva][2];
    double precioTotal = precios[indexHabitacion - 1] * numDias;

    printf("El costo total de su reserva es: %.2lf\n", precioTotal);
    printf("¿Desea pagar la reserva? (1: Sí, 2: No): ");
    int opcion;
    scanf("%d", &opcion);

    if (opcion == 1) {
        reservas[numReserva][3] = 2; // Cambiar estado de la reserva a pagado
        guardarReservas(reservas);
        printf("Reserva pagada exitosamente.\n");
    } else {
        printf("Reserva no pagada.\n");
    }
}

