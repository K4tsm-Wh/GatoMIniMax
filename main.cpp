#include <iostream>
#include <vector>

using namespace std;

struct Gato
{
    char tablero[3][3];
    char jugadorActual;

    void inicializar()
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

    void dibujar()
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

    bool mover(int fila, int col)
    {
        if (fila >= 0 && fila < 3 && col >= 0 && col < 3 && tablero[fila][col] == ' ')
        {
            tablero[fila][col] = jugadorActual;
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }
};

main()
{
    Gato gato;
    gato.inicializar();
    return 0;
}