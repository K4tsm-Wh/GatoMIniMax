# GatoMiniMax

Este proyecto implementa el juego Gato en C++, donde un jugador humano compite contra una Inteligencia Artificial que decide sus movimientos usando el algoritmo Minimax, con dos versiones del algoritmo para comparar su rendimiento.

**-Minimax sin poda:** revisa todas las jugadas posibles.

**-Minimax con poda Alfa-Beta:** Esta versión optimiza Minimax eliminando ramas del árbol de búsqueda que no pueden influir en la decisión final. Se utilizan dos valores, alpha que es el mejor valor encontrado para el jugador maximizador y beta que es el mejor valor encontrado para el jugador minimizador. Esto reduce significativamente la cantidad de nodos evaluados y el tiempo de ejecución.

La versión sin poda Alfa-Beta explora muchas más jugadas posibles, lo que hace que la primera jugada tarde alrededor de 2913 microsegundos, mientras que la versión con poda reduce drásticamente el árbol de búsqueda, logrando tiempos de aproximadamente 958 microsegundos, demostrando una mejora en eficiencia.

**Sistema de puntaje de la IA**

La función de evaluación asigna puntajes a cada línea del tablero:

-3 en línea (IA O): +100 puntos (victoria)

-2 en línea (IA) + 1 vacío: +10 puntos

-1 en línea (IA) + 2 vacíos: +1 punto

-2 en línea (Jugador X) + 1 vacío: −20 puntos (amenaza que debe bloquearse)

**Integrantes:** Jossette Doll, Luna Urizar  



