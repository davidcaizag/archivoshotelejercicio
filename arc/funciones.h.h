#ifndef FUNCIONES_H
#define FUNCIONES_H

void cargarHabitaciones(char habitaciones[][3][40], double precios[]);
void realizarReserva(char clientes[][2][40], char habitaciones[][3][40], int reservas[][4]);
void mostrarReservas(char clientes[][2][40], char habitaciones[][3][40], int reservas[][4]);
void pagarReserva(char habitaciones[][3][40], double precios[], int reservas[][4]);
void menuBuscarHabitacion(char habitaciones[][3][40], double precios[]);

#endif // FUNCIONES_H
