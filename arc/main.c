#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    char clientes[9][2][40] = {
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""},
        {"", ""}
    };

    char habitaciones[9][3][40] = {
        {"1", "simple", "Dan Carlton"},
        {"2", "doble", "Dan Carlton"},
        {"3", "triple", "Dan Carlton"},
        {"4", "simple", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "simple", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };

    double precios[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};

    int reservas[10][4] = {
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0},
        {-1, -1, -1, 0}
    };

    cargarClientes(clientes);
    cargarHabitaciones(habitaciones, precios);
    cargarReservas(reservas);

    int opcion, numHabitacion, numReserva;
    int numReservas[10], count;
    int numReservasPagar[10], countPagar;

    do {
        printf("Escoja una opcion:\n1.Buscar Habitacion\n2.Realizar reserva\n3.Ver reservas\n4.Pagar Reserva\n>>");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("1.Por tamano\n2.Por Hotel\n>>");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        buscarPorTamano(&numHabitacion, habitaciones, precios);
                        printf("La habitacion seleccionada es: %d\n", numHabitacion);
                        break;
                    case 2:
                        buscarHotel(&numHabitacion, habitaciones, precios);
                        printf("La habitacion seleccionada es: %d\n", numHabitacion);
                        break;
                    default:
                        printf("Opcion no valida.\n");
                        break;
                }
                break;
            case 2:
                realizarReserva(numHabitacion, habitaciones, clientes, reservas);
                break;
            case 3:
                count = buscarReservaPorCedula(numReservas, clientes, reservas);
                imprimirReserva(numReservas, count, clientes, reservas, habitaciones, precios);
                break;
            case 4:
                countPagar = buscarReservaPorCedula(numReservasPagar, clientes, reservas);
                if (countPagar != 0) {
                    pagarReserva(numReservasPagar[0], reservas, habitaciones, precios);
                }
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }
        printf("Desea elegir otra opcion? (1.SI 2.NO)\n>>");
        scanf("%d", &opcion);
    } while (opcion == 1);

    guardarClientes(clientes);
    guardarReservas(reservas);

    return 0;
}