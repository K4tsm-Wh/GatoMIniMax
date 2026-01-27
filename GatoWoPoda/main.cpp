#include "Gato.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    Gato gato;
    gato.inicializar();

    int fila, col;
    bool juegoActivo = true;

    while (juegoActivo)
    {
        gato.dibujar();

        if (gato.verificarGanador() != ' ' || gato.hayEmpate())
        {
            juegoActivo = false;
            break;
        }

        if (gato.getJugadorActual() == 'X')
        {
            cout << "Turno Jugador (X). Ingresa Fila y Columna (0-2): ";
            cin >> fila >> col;
            if (!gato.mover(fila, col))
            {
                cout << "Movimiento invalido, intenta de nuevo.\n";
            }
        }
        else
        {
            cout << "Turno IA (O) pensando...\n";
            gato.jugarIA();
        }
    }

    gato.dibujar();
    char ganador = gato.verificarGanador();
    if (ganador == ' ')
        cout << "Empate!\n";
    else
        cout << "Ganador: " << ganador << "!\n";

    return 0;
    
}
