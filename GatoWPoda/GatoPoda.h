
#pragma once
#include <iostream>
using namespace std;

class GatoPoda
{
private:
    char tablero[3][3];
    char jugadorActual;

public:
    GatoPoda(); 
    void inicializar();
    void dibujar();
    bool mover(int fila, int col);
    char verificarGanador();
    bool hayEmpate();
    int evaluarLinea(char a, char b, char c);
    int revisarPuntaje();
    int minimax(int profundidad, bool esMaximizar, int alpha, int beta);
    void jugarIA();
    char getJugadorActual();
};
