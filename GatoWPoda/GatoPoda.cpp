#include "GatoPoda.h"
#include <vector>
#include <algorithm>
#include <chrono>


GatoPoda::GatoPoda()
{
    inicializar();
}

void GatoPoda::inicializar()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tablero[i][j] = ' ';
        }
    }
    jugadorActual = 'X';
}

void GatoPoda::dibujar()
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << " ";
        if (i < 2)
            cout << "\n---|---|---\n";
    }
    cout << "\n";
}

bool GatoPoda::mover(int fila, int col)
{
    if (fila >= 0 && fila < 3 && col >= 0 && col < 3 && tablero[fila][col] == ' ')
    {
        tablero[fila][col] = jugadorActual;
        if (jugadorActual == 'X')
            jugadorActual = 'O';
        else
            jugadorActual = 'X';

        return true;
    }
    return false;
}

char GatoPoda::verificarGanador()
{
    for (int i = 0; i < 3; i++)
    {
        if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
            return tablero[i][0];
    }

    for (int i = 0; i < 3; i++)
    {
        if (tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])
            return tablero[0][i];
    }

    if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
        return tablero[0][0];

    if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])
        return tablero[0][2];

    return ' ';
}

bool GatoPoda::hayEmpate()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ')
                return false;

    return true;
}

int GatoPoda::evaluarLinea(char a, char b, char c)
{
    int puntos = 0;
        if (a == 'O' && b == 'O' && c == 'O')
        {
            puntos = 100;
        }
        else if ((a == 'O' && b == 'O' && c == ' ') || (a == 'O' && c == 'O' && b == ' ') || (b == 'O' && c == 'O' && a == ' '))
        {
            puntos = 10;
        }
        else if ((a == 'O' && b == ' ' && c == ' ') || (b == 'O' && a == ' ' && c == ' ') || (c == 'O' && a == ' ' && b == ' '))
        {
            puntos = 1;
        }
        else if ((a == 'X' && b == 'X' && c == ' ') || (a == 'X' && c == 'X' && b == ' ') || (b == 'X' && c == 'X' && a == ' '))
        {
            puntos = -20;
        }

        return puntos;  
}

int GatoPoda::revisarPuntaje()
{
    int puntaje = 0;

    for (int i = 0; i < 3; i++)
    {
        puntaje += evaluarLinea(tablero[i][0], tablero[i][1], tablero[i][2]);
        puntaje += evaluarLinea(tablero[0][i], tablero[1][i], tablero[2][i]);
    }

    puntaje += evaluarLinea(tablero[0][0], tablero[1][1], tablero[2][2]);
    puntaje += evaluarLinea(tablero[0][2], tablero[1][1], tablero[2][0]);

    return puntaje;
}

int GatoPoda::minimax(int profundidad, bool esMaximizar, int alpha, int beta)
{
    char ganador = verificarGanador();

    if (ganador == 'O')
        return 1000 - profundidad;
    if (ganador == 'X')
        return -1000 + profundidad;
    if (hayEmpate())
        return 0;
    
    if (profundidad > 4)
            return revisarPuntaje();

    if (esMaximizar)
    {
        int mejor = -99999;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tablero[i][j] == ' ')
                {
                    tablero[i][j] = 'O';
                    int puntaje = minimax(profundidad + 1, false, alpha, beta);
                    tablero[i][j] = ' ';

                    mejor = max(mejor, puntaje);
                    alpha = max(alpha, mejor);

                    if (beta <= alpha)
                        break; 
                }
            }
        }
        return mejor;
    }
    else
    {
        int mejor = 99999;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tablero[i][j] == ' ')
                {
                    tablero[i][j] = 'X';
                    int puntaje = minimax(profundidad + 1, true, alpha, beta);
                    tablero[i][j] = ' ';

                    mejor = min(mejor, puntaje);
                    beta = min(beta, mejor);

                    if (beta <= alpha)
                        break; 
                }
            }
        }
        return mejor;
    } 
    }

void GatoPoda::jugarIA()
{
     using namespace std::chrono; 
     auto inicio = high_resolution_clock::now();
    
     int mejorPuntaje = -99999;
        int fila = -1, col = -1;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tablero[i][j] == ' ')
                {
                    tablero[i][j] = 'O';
                    int puntaje = minimax(0, false, -99999, 99999);
                    tablero[i][j] = ' ';

                    if (puntaje > mejorPuntaje)
                    {
                        mejorPuntaje = puntaje;
                        fila = i;
                        col = j;
                    }
                }
            }
        }
        if (fila != -1)
        {
            mover(fila, col);
        }
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Tiempo IA: " << duracion.count() << " microsegundos" << endl;
}

char GatoPoda::getJugadorActual()
{
    return jugadorActual;
}
