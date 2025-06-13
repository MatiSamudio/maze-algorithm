# maze-algorithm

Este proyecto implementa un generador y solucionador de laberintos en consola, utilizando algoritmos clásicos de grafos. Está desarrollado en C++ con una interfaz ASCII que permite visualizar la construcción y resolución del laberinto paso a paso.

  Generación del laberinto: 
  
El laberinto se genera con un algoritmo de búsqueda en profundidad recursiva (DFS Backtracking). 
A partir de la celda inicial (0,0), el algoritmo:
Marca la celda como visitada.
Mezcla aleatoriamente las 4 direcciones posibles.
Avanza hacia celdas no visitadas, eliminando las paredes entre la actual y la siguiente.
Se llama recursivamente para seguir expandiendo el laberinto hasta visitar todas las celdas.
Este método garantiza un laberinto perfect maze (sin ciclos ni caminos redundantes).

  Resolución del laberinto:
   
Se ofrecen dos formas de resolver el laberinto:
DFS Backtracking: 
intenta avanzar por caminos posibles y retrocede cuando llega a un callejón sin salida.
BFS (Breadth-First Search): 
explora el laberinto en anchura, asegurando encontrar el camino más corto desde la entrada a la salida.
Ambos métodos muestran visualmente los caminos explorados (x) y la solución final (.).
 
  Descubrimientos y análisis:
   
Durante el desarrollo se midieron los tiempos de ejecución de los algoritmos en distintos tamaños de laberintos. 
Se observó que:
DFS es más rápido en laberintos pequeños, pero no garantiza el camino más corto.
BFS es más lento en promedio, pero siempre encuentra la ruta óptima.

  Qué haría diferente:

Modularizar aún más las funciones, especialmente separando entrada/salida de lógica pura.
Agregar control de profundidad y conteo de pasos para comparar eficiencia.
Evaluar otros algoritmos de generación como Prim o Kruskal para mayor variedad estructural.

