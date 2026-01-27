#include "Gato.h"
#include <vector>
#include <algorithm>
#include <chrono>


Gato::Gato()
{
    inicializar();
}

void Gato::inicializar()
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

void Gato::dibujar()
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

bool Gato::mover(int fila, int col)
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

char Gato::verificarGanador()
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

bool Gato::hayEmpate()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ')
                return false;

    return true;
}

int Gato::evaluarLinea(char a, char b, char c)
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

int Gato::revisarPuntaje()
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

int Gato::minimax(int profundidad, bool esMaximizar)
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
            int mejorPuntaje = -99999;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (tablero[i][j] == ' ')
                    {
                        tablero[i][j] = 'O';
                        int puntaje = minimax(profundidad + 1, false);
                        puntaje += revisarPuntaje();
                        tablero[i][j] = ' ';
                        mejorPuntaje = max(mejorPuntaje, puntaje);
                    }
                }
            }
            return mejorPuntaje;
        }
        else
        {
            int mejorPuntaje = 99999;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (tablero[i][j] == ' ')
                    {
                        tablero[i][j] = 'X';
                        int puntaje = minimax(profundidad + 1, true);
                        tablero[i][j] = ' ';
                        mejorPuntaje = min(mejorPuntaje, puntaje);
                    }
                }
            }
            return mejorPuntaje;
        }
    }

void Gato::jugarIA()
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
                    int puntaje = minimax(0, false);
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

char Gato::getJugadorActual()
{
    return jugadorActual;
}
