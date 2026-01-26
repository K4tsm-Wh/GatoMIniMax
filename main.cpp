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

char verificarGanador(){

        for (int i = 0; i <  3; i++) {

            if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] ){
                return tablero[i][0];}

            if (tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] ){
                return tablero[0][i];}}

        if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]){
            return tablero[0][0];}

        if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]){
            return tablero[0][2];}

    return ' ';}

 int evaluarLinea(char a, char b, char c) {

            int puntos = 0;

            if (a == 'O' && b == 'O' && c == 'O') {
                puntos = 100;}
            else if ((a == 'O' && b == 'O' && c == ' ') || (a == 'O' && c == 'O' && b == ' ') || (b == 'O' && c == 'O' && a == ' ')) {
                puntos = 10;}
            else if ((a == 'O' && b == ' ' && c == ' ') || (b == 'O' && a == ' ' && c == ' ') ||(c == 'O' && a == ' ' && b == ' ')) {
                puntos = 1;}
            else if ((a == 'X' && b == 'X' && c == ' ') || (a == 'X' && c == 'X' && b == ' ') ||(b == 'X' && c == 'X' && a == ' ')) {
                puntos = -20;}

            return puntos;}

        int revisarPuntaje() {

            int puntaje = 0;

            for (int i = 0; i < 3; i++){
                puntaje += evaluarLinea(tablero[i][0], tablero[i][1], tablero[i][2]);}

            for (int j = 0; j < 3; j++){
                puntaje += evaluarLinea(tablero[0][j], tablero[1][j], tablero[2][j]);}

            puntaje += evaluarLinea(tablero[0][0], tablero[1][1], tablero[2][2]);
            puntaje += evaluarLinea(tablero[0][2], tablero[1][1], tablero[2][0]);

            return puntaje;}

main()
{
    Gato gato;
    gato.inicializar();
    return 0;
}
