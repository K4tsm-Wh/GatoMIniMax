#pragma once
#include <iostream>
using namespace std;

class Gato
{
private:
    char tablero[3][3];
    char jugadorActual;

public:
    Gato(); 
    void inicializar();
    void dibujar();
    bool mover(int fila, int col);
    char verificarGanador();
    bool hayEmpate();
    int evaluarLinea(char a, char b, char c);
    int revisarPuntaje();
    int minimax(int profundidad, bool esMaximizar);
    void jugarIA();
    char getJugadorActual();
};
